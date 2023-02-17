/***************************************************************************
                          setupdialog.cpp  -  description
                             -------------------
    begin                : sept 2011
    copyright            : (C) 2011 by Jaime Robles
    email                : jaime@robles.es
 ***************************************************************************/

/*****************************************************************************
 * This file is part of KLog.                                                *
 *                                                                           *
 *    KLog is free software: you can redistribute it and/or modify           *
 *    it under the terms of the GNU General Public License as published by   *
 *    the Free Software Foundation, either version 3 of the License, or      *
 *    (at your option) any later version.                                    *
 *                                                                           *
 *    KLog is distributed in the hope that it will be useful,                *
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *    GNU General Public License for more details.                           *
 *                                                                           *
 *    You should have received a copy of the GNU General Public License      *
 *    along with KLog.  If not, see <https://www.gnu.org/licenses/>.         *
 *                                                                           *
 *****************************************************************************/

#include "setupdialog.h"
//#include <QDebug>

/*
This class calls all the othet "Setup..." to manage the configuration

*/

SetupDialog::SetupDialog(DataProxy_SQLite *dp, QWidget *parent)
{
    //qDebug() << Q_FUNC_INFO << ": " << _configFile << "/" << _softwareVersion << "/" << QString::number(_page) << util->boolToQString(_firstTime);

    logLevel = None;
    constrid = 2;
    nolog = true;
    util = new Utilities(Q_FUNC_INFO);
    firstTime = true;
    latestBackup = QString();
    dataProxy = dp;

    configFileName = QString();
    version = QString();
    pageRequested = 0;

    int logsPageTabN=-1;
    //qDebug() << Q_FUNC_INFO << ": 01";

    locator = new Locator();

    tabWidget = new QTabWidget;
    //qDebug() << Q_FUNC_INFO << ": 01.0";
    userDataPage = new SetupPageUserDataPage(dataProxy);
    //qDebug() << Q_FUNC_INFO << ": 01.10";
    bandModePage = new SetupPageBandMode(dataProxy, this);
    //qDebug() << Q_FUNC_INFO << ": 01.20";
    dxClusterPage = new SetupPageDxCluster(this);
    //qDebug() << Q_FUNC_INFO << ": 01.30";
    colorsPage = new SetupPageColors(this);
    //qDebug() << Q_FUNC_INFO << ": 01.40";
    miscPage = new SetupPageMisc(this);
    //qDebug() << Q_FUNC_INFO << ": 01.50";
    worldEditorPage = new SetupPageWorldEditor (dataProxy, this);
    //qDebug() << Q_FUNC_INFO << ": 01.60";
    logsPage = new SetupPageLogs(dataProxy, this);
    //qDebug() << Q_FUNC_INFO << ": 01.70";
    eLogPage = new SetupPageELog(this);
    //qDebug() << Q_FUNC_INFO << ": 01.80";
    UDPPage = new SetupPageUDP(this);
    //qDebug() << Q_FUNC_INFO << ": 01.90";
    satsPage = new SetupPageSats(dataProxy, this);
    //qDebug() << Q_FUNC_INFO << ": 01.100";
    hamlibPage = new SetupPageHamLib(dataProxy, this);
    //qDebug() << Q_FUNC_INFO << ": 01.101";
    logViewPage = new SetupPageLogView(dataProxy, this);
    //qDebug() << Q_FUNC_INFO << ": 02";

    tabWidget->addTab(userDataPage, tr("User data"));
    tabWidget->addTab(bandModePage, tr("Bands/Modes"));
    tabWidget->addTab(logViewPage, tr("Log widget"));
    tabWidget->addTab(dxClusterPage, tr("D&X-Cluster"));
    tabWidget->addTab(colorsPage, tr("Colors"));
    tabWidget->addTab(miscPage, tr("Misc"));
    tabWidget->addTab(worldEditorPage, tr("World Editor"));
    logsPageTabN = tabWidget->addTab(logsPage, tr("Logs"));
    tabWidget->addTab(eLogPage, tr("eLog"));
    tabWidget->addTab(UDPPage, tr("WSJT-X"));
    tabWidget->addTab(satsPage , tr("Satellites"));
    //qDebug() << Q_FUNC_INFO << ": 02.100";
    tabWidget->addTab(hamlibPage, tr ("HamLib"));
    //qDebug() << "SetupDialog::SetupDialog 03";

    closeButton = new QPushButton(tr("Cancel"));
    okButton = new QPushButton(tr("OK"));

    QHBoxLayout *horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(tabWidget);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(okButton);
    buttonsLayout->addWidget(closeButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(horizontalLayout);
    mainLayout->addLayout(buttonsLayout);

    //qDebug() << Q_FUNC_INFO << ": 04";

    setLayout(mainLayout);
    setWindowTitle(tr("Settings"));

    //connectActions();
    //qDebug() << Q_FUNC_INFO << " - END";
}

void SetupDialog::init(const QString &_configFile, const QString &_softwareVersion, const int _page, const bool _firstTime)
{
    util->setLongPrefixes(dataProxy->getLongPrefixes());
    util->setSpecialCalls(dataProxy->getSpecialCallsigns());
    firstTime = _firstTime;
    configFileName = _configFile;
    version = _softwareVersion;
    pageRequested = _page;

    slotReadConfigData();
    //qDebug() << Q_FUNC_INFO << ": 05.1";

    if ((pageRequested==6) && (logsPageTabN>0))// The user is opening a new log
    {
        //qDebug() << Q_FUNC_INFO << ": 5.2";
        tabWidget->setCurrentIndex(logsPageTabN);
    }
    //qDebug() << Q_FUNC_INFO << ": 5.3";
    nolog = !(haveAtleastOneLog());

    connectActions();
    //qDebug() << Q_FUNC_INFO << " - END";
}

SetupDialog::~SetupDialog()
{
    //qDebug() << Q_FUNC_INFO ;
    delete(locator);
    delete(userDataPage);
    delete(bandModePage);
    delete(dxClusterPage);
    delete(miscPage);
    delete(worldEditorPage);
    delete(logsPage);
    delete(eLogPage);
    delete(colorsPage);
    delete(UDPPage);
    delete(satsPage);
    delete(hamlibPage);
    delete(logViewPage);
    delete(util);
}

void SetupDialog::connectActions()
{
    //qDebug() << Q_FUNC_INFO;
    logEvent(Q_FUNC_INFO, "Start", Debug);
    connect(closeButton, SIGNAL(clicked()), this, SLOT(slotCancelButtonClicked()));
    connect(okButton, SIGNAL(clicked()), this, SLOT(slotOkButtonClicked()));
    connect (logsPage, SIGNAL(newLogData(QStringList)), this, SLOT(slotAnalyzeNewLogData(QStringList)));
    connect(logsPage, SIGNAL(focusOK()), this, SLOT(slotFocusOK()) );
    connect (userDataPage, SIGNAL(mainCallsignSignal(QString)), this, SLOT(slotSetStationCallSign(QString)));
    connect (userDataPage, SIGNAL(operatorsSignal(QString)), this, SLOT(slotSetOperators(QString)));
    connect (userDataPage, SIGNAL(enterKey()), this, SLOT(slotOkButtonClicked()));
    //connect (lotwPage, SIGNAL(enterKey()), this, SLOT(slotOkButtonClicked()));
    connect (eLogPage, SIGNAL(enterKey()), this, SLOT(slotOkButtonClicked()));
    //connect (clubLogPage, SIGNAL(enterKey()), this, SLOT(slotOkButtonClicked()));
    connect (eLogPage, SIGNAL(qrzcomAuto(bool)), this, SLOT(slotQRZCOMAuto(bool)));

    logEvent(Q_FUNC_INFO, "END", Debug);
}

void SetupDialog::slotQRZCOMAuto(const bool _b)
{
    emit qrzcomAuto(_b);
}

void SetupDialog::setData(const QString &_configFile, const QString &_softwareVersion, const int _page, const bool _firstTime)
{
      //qDebug() << "SetupDialog::setData: " << "/" << _configFile << "/" << _softwareVersion << "/" << QString::number(_page);
    logEvent(Q_FUNC_INFO, "Start", Debug);
    nolog = !(haveAtleastOneLog());
    firstTime = _firstTime;
    if (firstTime)
    {
          //qDebug() << "SetupDialog::setData FIRST TIME! ";
    }
    else
    {
          //qDebug() << "SetupDialog::setData NOT FIRST TIME! ";
        miscPage->setUseDefaultDBPath(miscPage->getDefaultDBPath());
    }

    setConfigFile(_configFile);
    setSoftVersion(_softwareVersion);
    slotReadConfigData ();
    setPage(_page);
    //removeBandModeDuplicates();
    logEvent(Q_FUNC_INFO, "END", Debug);
      //qDebug() << "SetupDialog::setData - END";
}

void SetupDialog::setConfigFile(const QString &_configFile)
{
       //qDebug() << "SetupDialog::setConfigFile";
    logEvent(Q_FUNC_INFO, "Start", Debug);
    configFileName = _configFile;
    logEvent(Q_FUNC_INFO, "END", Debug);
}

void SetupDialog::setSoftVersion(const QString &_softwareVersion)
{
       //qDebug() << "SetupDialog::setSoftVersion";
    logEvent(Q_FUNC_INFO, "Start", Debug);
    version = _softwareVersion;
    logEvent(Q_FUNC_INFO, "END", Debug);
}


void SetupDialog::setPage(const int _page)
{
       //qDebug() << "SetupDialog::setPage("<<QString::number(_page) << ")";
    logEvent(Q_FUNC_INFO, "Start", Debug);
    pageRequested = _page;

    if ((pageRequested==6) && (logsPageTabN>0))// The user is opening a new log
    {
        tabWidget->setCurrentIndex(pageRequested);
    }
    logEvent(Q_FUNC_INFO, "END", Debug);
}

void SetupDialog::slotCancelButtonClicked()
{
      //qDebug() << "SetupDialog::slotCancelButtonClicked";
    logEvent(Q_FUNC_INFO, "Start", Debug);
    if (firstTime || nolog)
    {
        if (nolog)
        {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Information);
            msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            msgBox.setDefaultButton(QMessageBox::Yes);
            msgBox.setText(tr("You need to enter at least one log in the Logs tab."));
            msgBox.setInformativeText(tr("Do you want to add one log in the Logs tab or exit KLog?\n(Click Yes to add a log or No to exit KLog)"));
            int ret = msgBox.exec();
            if (ret == QMessageBox::No)
            {
                emit debugLog (Q_FUNC_INFO, "END-1", logLevel);
                emit exitSignal(2);
                return;
            }
            else
            {
                emit debugLog (Q_FUNC_INFO, "END-2", logLevel);
                return;
            }
        }
    }
    hamlibPage->stopHamlib();
    QDialog::reject ();
    close();
    logEvent(Q_FUNC_INFO, "END", Debug);
}

void SetupDialog::createIcons()
{
       //qDebug() << "SetupDialog::createIcons";
    logEvent(Q_FUNC_INFO, "Start", Debug);
    QListWidgetItem *configButton = new QListWidgetItem(contentsWidget);
    configButton->setIcon(QIcon(":/images/config.png"));
    configButton->setText(tr("User data"));
    configButton->setTextAlignment(Qt::AlignHCenter);
    configButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *logsButton = new QListWidgetItem(contentsWidget);
    logsButton->setIcon(QIcon(":/images/config.png"));
    logsButton->setText(tr("Logs"));
    logsButton->setTextAlignment(Qt::AlignHCenter);
    logsButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *bandsButton = new QListWidgetItem(contentsWidget);
    bandsButton->setIcon(QIcon(":/images/query.png"));
    bandsButton->setText(tr("Bands/Modes"));
    bandsButton->setTextAlignment(Qt::AlignHCenter);
    bandsButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *dxClusterButton = new QListWidgetItem(contentsWidget);
    dxClusterButton->setIcon(QIcon(":/images/query.png"));
    dxClusterButton->setText(tr("DX-Cluster"));
    dxClusterButton->setTextAlignment(Qt::AlignHCenter);
    dxClusterButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *colorsButton  = new QListWidgetItem(contentsWidget);
    colorsButton->setIcon(QIcon(":/images/query.png"));
    colorsButton->setText(tr("Colors"));
    colorsButton->setTextAlignment(Qt::AlignHCenter);
    colorsButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *miscButton  = new QListWidgetItem(contentsWidget);
    miscButton->setIcon(QIcon(":/images/query.png"));
    miscButton->setText(tr("Misc"));
    miscButton->setTextAlignment(Qt::AlignHCenter);
    miscButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *worldButton  = new QListWidgetItem(contentsWidget);
    worldButton->setIcon(QIcon(":/images/query.png"));
    worldButton->setText(tr("World"));
    worldButton->setTextAlignment(Qt::AlignHCenter);
    worldButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    connect(contentsWidget,
            SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
            this, SLOT(changePage(QListWidgetItem*,QListWidgetItem*)));
    logEvent(Q_FUNC_INFO, "END", Debug);
}

void SetupDialog::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
       //qDebug() << "SetupDialog::changePage";
    logEvent(Q_FUNC_INFO, "Start", Debug);
    if (!current)
        current = previous;

    pagesWidget->setCurrentIndex(contentsWidget->row(current));
    logEvent(Q_FUNC_INFO, "END", Debug);
}



void SetupDialog::slotOkButtonClicked()
{
    //qDebug() << Q_FUNC_INFO ;
    logEvent(Q_FUNC_INFO, "Start", Debug);

    if (!miscPage->areDBPathChangesApplied())
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText(tr("DB has not been moved to new path."));
        msgBox.setInformativeText(tr("Go to the Misc tab and click on Move DB\n or the DB will not be moved to the new location."));
        msgBox.exec();
        emit debugLog (Q_FUNC_INFO, "END-1", logLevel);
        return;
    }

    if (!util->isValidCall(userDataPage->getMainCallsign())){ //
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText(tr("You need to enter at least a valid callsign."));
        msgBox.setInformativeText(tr("Go to the User tab and enter valid callsign."));
        msgBox.exec();
        emit debugLog (Q_FUNC_INFO, "END-2", logLevel);
        return;
    }

    if (!haveAtleastOneLog())
    {
        //qDebug() << "SetupDialog::slotOkButtonClicked - NO LOG!";
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText(tr("You have not selected the kind of log you want."));
        msgBox.setInformativeText(tr("You will be redirected to the Log tab.\nPlease add and select the kind of log you want to use."));
        msgBox.exec();

        tabWidget->setCurrentIndex(tabWidget->indexOf(logsPage));
        logsPage->createNewLog();
        //emit newLogRequested(true); // Signal to be catched by logsPage true show new log

        emit debugLog (Q_FUNC_INFO, "END-3", logLevel);
        return;
    }
    //qDebug() << "SetupDialog::slotOkButtonClicked - 10";
    QFile file (configFileName);


    if (!file.open (QIODevice::WriteOnly))   /* Flawfinder: ignore */
    {
      QDialog::reject();
    }
    QTextStream stream (&file);

        //QRZ/CQ/ITU/CONTEST
    stream << "Version=" << version << ";";
    stream << "Callsign="  << userDataPage->getMainCallsign() << ";";
    if ((userDataPage->getOperators()).length() >= 3)
    { // There are no valid calls with less than 3 Chars
        stream << "Operators="  << userDataPage->getOperators() << ";";
    }
    stream << "CQz=" << QString::number(userDataPage->getCQz()) <<  ";" <<  QT_ENDL;
    stream << "ITUz=" << QString::number(userDataPage->getITUz()) <<  ";" <<  QT_ENDL;

    if ( locator->isValidLocator(userDataPage->getStationLocator()) )
    {
        stream << "StationLocator=" << userDataPage->getStationLocator() << ";";
    }

    if ((!(userDataPage->getName()).isNull()) && (  (userDataPage->getName()).length() > 0   ))
    {
        stream << "Name=" << userDataPage->getName() <<";";
    }
    if ((!(userDataPage->getAddress1()).isNull()) && (  (userDataPage->getAddress1()).length() > 0   ))
    {
        stream << "Address1=" << userDataPage->getAddress1() <<";";
        }
        if ((!(userDataPage->getAddress2()).isNull())  && (  (userDataPage->getAddress2()).length() > 0   ))
        {
            stream << "Address2=" << userDataPage->getAddress2() <<";";
        }
        if ((!(userDataPage->getAddress3()).isNull()) && (  (userDataPage->getAddress3()).length() > 0   ))
        {
            stream << "Address3=" << userDataPage->getAddress3() <<";";
        }
        if ((!(userDataPage->getAddress4()).isNull()) && (  (userDataPage->getAddress4()).length() > 0   ))
        {
            stream << "Address4=" << userDataPage->getAddress4() <<";";
        }

        if ((!(userDataPage->getCity()).isNull()) && (  (userDataPage->getCity()).length() > 0   ))
        {
            stream << "City=" << userDataPage->getCity() <<";";
        }
        if ((!(userDataPage->getZipCode()).isNull()) && (  (userDataPage->getZipCode()).length() > 0   ))
        {
            stream << "ZipCode=" << userDataPage->getZipCode() <<";";
        }
        if ((!(userDataPage->getProvince()).isNull()) && (  (userDataPage->getProvince()).length() > 0   ))
        {
            stream << "ProvinceState=" << userDataPage->getProvince() <<";";
        }
        if ((!(userDataPage->getCountry()).isNull()) && (  (userDataPage->getCountry()).length() > 0   ))
        {
            stream << "Country=" << userDataPage->getCountry() <<";";
        }
        if ((!(userDataPage->getRig1()).isNull()) && (  (userDataPage->getRig1()).length() > 0   ))
        {
            stream << "Rig1=" << userDataPage->getRig1() <<";";
        }
        if ((!(userDataPage->getRig2()).isNull()) && (  (userDataPage->getRig2()).length() > 0   ))
        {
            stream << "Rig2=" << userDataPage->getRig2() <<";";
        }
        if ((!(userDataPage->getRig3()).isNull()) && (  (userDataPage->getRig3()).length() > 0   ))
        {
            stream << "Rig3=" << userDataPage->getRig3() <<";";
        }
        if ((!(userDataPage->getAntenna1()).isNull()) && (  (userDataPage->getAntenna1()).length() > 0   ))
        {
            stream << "Antenna1=" << userDataPage->getAntenna1() <<";";
        }
        if ((!(userDataPage->getAntenna2()).isNull()) && (  (userDataPage->getAntenna2()).length() > 0   ))
        {
            stream << "Antenna2=" << userDataPage->getAntenna2() <<";";
        }
        if ((!(userDataPage->getAntenna3()).isNull()) && (  (userDataPage->getAntenna2()).length() > 0   ))
        {
            stream << "Antenna3=" << userDataPage->getAntenna3() <<";";
        }
        if ((userDataPage->getPower()).toFloat()>=0)
        {
            stream << "Power=" << userDataPage->getPower() << ";";
        }
        //qDebug() << "SetupDialog::slotOkButtonClicked - 20";

        stream << "Bands=" << bandModePage->getBands() << ";" <<  QT_ENDL;
        stream << "Modes=" << bandModePage->getModes() << ";" <<  QT_ENDL;
        stream << "LogViewFields=" << logViewPage->getFields() << ";" <<  QT_ENDL;

        //stream << "InMemory=" << miscPage->getInMemory() << ";" <<  QT_ENDL;
        stream << "RealTime=" << miscPage->getRealTime() << ";" <<  QT_ENDL;
        stream << "ShowSeconds=" << util->boolToQString(miscPage->getShowSeconds())<< ";" <<  QT_ENDL;
        stream << "UTCTime=" << miscPage->getUTCTime() << ";" <<  QT_ENDL;
        stream << "AlwaysADIF=" << miscPage->getAlwaysADIF() << ";" <<  QT_ENDL;
        stream << "UseDefaultName=" << miscPage->getUseDefaultName() << ";" <<  QT_ENDL;
        stream << "DefaultADIFFile=" << miscPage->getDefaultFileName() << ";" <<  QT_ENDL;
        stream << "DBPath=" << miscPage->getDefaultDBPath() << ";" <<  QT_ENDL;
        stream << "ImperialSystem=" << miscPage->getImperial() << ";" <<  QT_ENDL;
        stream << "SendQSLWhenRec=" << miscPage->getSendQSLWhenRec() << ";" <<  QT_ENDL;
        stream << "ShowCallsignInSearch=" << miscPage->getShowStationCallSignInSearch() << ";" <<  QT_ENDL;
        stream << "CompleteWithPrevious=" << miscPage->getCompleteWithPrevious() << ";" <<  QT_ENDL;
        stream << "CheckNewVersions=" << miscPage->getCheckNewVersions() << ";" <<  QT_ENDL;
        stream << "ManageDXMarathon=" << miscPage->getDXMarathon() << ";" <<  QT_ENDL;
        stream << "DebugLog=" << miscPage->getDebugLogLevel() << ";";
        stream << "SendEQSLByDefault=" << miscPage->getSendEQSLByDefault() << ";";
        stream << "DeleteAlwaysAdiFile=" << miscPage->getDeleteAlwaysAdiFile() << ";";
        stream << "CheckValidCalls=" << util->boolToQString (miscPage->getCheckCalls())<< ";";

        if (miscPage->getDupeTime()>0)
        {
            stream << "DuplicatedQSOSlot=" << QString::number(miscPage->getDupeTime()) << ";";
        }

        //stream << "PSTRotatorActive=" << interfacesWindowsPage->getSendToPSTRotator() << ";";
        //stream << "PSTRotatorServer=" << interfacesWindowsPage->getPSTRotatorUDPServer() << ";";
        //stream << "PSTRotatorPort=" << interfacesWindowsPage->getPSTRotatorUDPServerPort() << ";";

        //qDebug() << "SetupDialog::slotOkButtonClicked - 30";

        if ( miscPage->getReportInfo())
        {
            stream << "ProvideInfo=True;"  <<  QT_ENDL;
        }
        QString tmp;
        tmp = dxClusterPage->getSelectedDxClusterServer();
        if (!(tmp.isNull()) && (  tmp.length() > 0   ))
        {
            stream << "DXClusterServerToUse=" << tmp <<";";
        }

        QStringList stringList;
        stringList.clear();
        stringList << dxClusterPage->getDxclusterServersComboBox();

        if (stringList.size()>0)
        {
            for (int i = 0; i < stringList.size(); i++)
            {
                 stream << "DXClusterServerPort="<< stringList.at(i) << ";";
            }
        }
        stream << "DXClusterShowHF=" << dxClusterPage->getShowHFQCheckbox() << ";" <<  QT_ENDL;
        stream << "DXClusterShowVHF=" << dxClusterPage->getShowVHFQCheckbox() << ";" <<  QT_ENDL;
        stream << "DXClusterShowWARC=" << dxClusterPage->getShowWARCQCheckbox() << ";" <<  QT_ENDL;
        stream << "DXClusterShowWorked=" << dxClusterPage->getShowWorkedQCheckbox() << ";" <<  QT_ENDL;
        stream << "DXClusterShowConfirmed=" << dxClusterPage->getShowConfirmedQCheckbox() << ";" <<  QT_ENDL;
        stream << "DXClusterShowAnn=" << dxClusterPage->getShowANNQCheckbox() << ";" <<  QT_ENDL;
        stream << "DXClusterShowWWV=" << dxClusterPage->getShowWWVQCheckbox() << ";" <<  QT_ENDL;
        stream << "DXClusterShowWCY=" << dxClusterPage->getShowWCYQCheckbox() << ";" <<  QT_ENDL;
        stream << "DXClusterSave=" << dxClusterPage->getSaveActivityQCheckbox() << ";" <<  QT_ENDL;
        stream << "DXClusterSendToMap=" << dxClusterPage->getSendSpotsToMap()<< ";" <<  QT_ENDL;


        stream << "NewOneColor=" << colorsPage->getNewOneColor() << ";" <<  QT_ENDL;
        stream << "NeededColor=" << colorsPage->getNeededColor() << ";" <<  QT_ENDL;
        stream << "WorkedColor=" << colorsPage->getWorkedColor() << ";" <<  QT_ENDL;
        stream << "ConfirmedColor=" << colorsPage->getConfirmedColor() << ";" <<  QT_ENDL;
        stream << "DefaultColor=" << colorsPage->getDefaultColor() << ";" <<  QT_ENDL;
        stream << "DarkMode=" << colorsPage->getDarkMode() << ";";
        stream << "SelectedLog=" << QString::number(logsPage->getSelectedLog()) << ";" <<  QT_ENDL;
        //qDebug() << "SetupDialog::slotOkButtonClicked SelectedLog: " << logsPage->getSelectedLog();
        // CLUBLOG
        //qDebug() << "SetupDialog::slotOkButtonClicked - 40";

            if (eLogPage->getClubLogActive())
            {
                stream << "ClubLogActive=True;"<<  QT_ENDL;
            }
            else
            {
                stream << "ClubLogActive=False;"<< QT_ENDL;
            }
            if (eLogPage->getClubLogRealTime())
            {
                stream << "ClubLogRealTime=True;" <<  QT_ENDL;
            }
            else
            {
                stream << "ClubLogRealTime=False;";
            }
            tmp = eLogPage->getClubLogEmail() ;
            if (tmp.length()>0)
            {
                 stream << "ClubLogEmail=" << tmp << ";" <<  QT_ENDL;
            }

            tmp = eLogPage->getClubLogPassword() ;
            if (tmp.length()>0)
            {
                stream << "ClubLogPass=" << tmp << ";" <<  QT_ENDL;
            }

        //qDebug() << "SetupDialog::slotOkButtonClicked - 50";
        // eQSL

            if (eLogPage->getEQSLActive())
            {
                stream << "eQSLActive=True;" <<  QT_ENDL;
            }
            else
            {
                stream << "eQSLActive=False;";
            }
            tmp = eLogPage->getEQSLUser();
            if (tmp.length()>0)
            {
                 stream << "eQSLCall=" << tmp << ";" <<  QT_ENDL;
            }

            tmp = eLogPage->getEQSLPassword() ;
            if (tmp.length()>0)
            {
                stream << "eQSLPass=" << tmp << ";" <<  QT_ENDL;
            }

        // eQSL - END
        // QRZ.com

            //qDebug() << "SetupDialog::slotOkButtonClicked - Storing QRZ.com data";

            if (eLogPage->getQRZCOMActive())
            {
                stream << "QRZcomActive=True;" <<  QT_ENDL;
            }
            else
            {
                stream << "QRZcomActive=False;";
            }
            tmp = eLogPage->getQRZCOMUser();
            if (tmp.length()>0)
            {
                 stream << "QRZcomUser=" << tmp << ";" <<  QT_ENDL;
            }
            tmp = eLogPage->getQRZCOMPassword();
            if (tmp.length()>0)
            {
                 stream << "QRZcomPass=" << tmp << ";" <<  QT_ENDL;
            }

            if (eLogPage->getQRZCOMSubscriber())
            {
                 stream << "QRZcomSubscriber=True;";
            }
            else
            {
                stream << "QRZcomSubscriber=False;" <<  QT_ENDL;
            }

            if (eLogPage->getQRZCOMAutoCheck())
            {
                 stream << "QRZcomAuto=True;";
            }
            else
            {
                stream << "QRZcomAuto=False;" <<  QT_ENDL;
            }
            tmp = eLogPage->getQRZCOMLogBookKEY();
            if (tmp.length()>0)
            {
                 stream << "QRZcomLogBookKey=" << tmp << ";" <<  QT_ENDL;
            }

        // QRZ.com - END

        //qDebug() << "SetupDialog::slotOkButtonClicked - 60";

        // LOTW
        stream << "LoTWActive=" << util->boolToQString(eLogPage->getLoTWActive()) << ";" <<  QT_ENDL;
        tmp = eLogPage->getTQSLPath();
        if (tmp.length()>0)
        {
            stream << "LoTWPath=" << tmp << ";" <<  QT_ENDL;
        }
        tmp = eLogPage->getLoTWUser();
        if (tmp.length()>0)
        {
            stream << "LoTWUSer=" << tmp << ";" <<  QT_ENDL;
        }
        tmp = eLogPage->getLoTWPass();
        if (tmp.length()>0)
        {
            stream << "LoTWPass=" << tmp << ";" <<  QT_ENDL;
        }

        // LOTW
        //qDebug() << "SetupDialog::slotOkButtonClicked - 70";
        //WSJTX
        stream << "UDPServer=" << UDPPage->getUDPServer() << ";" <<  QT_ENDL;
        stream << "UDPNetworkInterface=" << UDPPage->getNetworkInterface() << ";" <<  QT_ENDL;
        stream << "UDPServerPort=" << UDPPage->getUDPServerPort() << ";" <<  QT_ENDL;
        stream << "LogFromWSJTX=" << UDPPage->getLogFromWSJTx() << ";" <<  QT_ENDL;
        stream << "LogAutoFromWSJTX=" << UDPPage->getAutoLogFromWSJTx() << ";" <<  QT_ENDL;
        stream << "RealTimeFromWSJTX=" << UDPPage->getReaDataFromWSJTx() << ";" <<  QT_ENDL;
        stream << "InfoTimeOut=" << UDPPage->getTimeout() << ";" <<  QT_ENDL;

          //qDebug() << "SetupDialog::slotOkButtonClicked: hamlib";
        QString _aa = hamlibPage->getData();
        stream << _aa;

          //qDebug() << "SetupDialog::slotOkButtonClicked: hamlib-2: " << _aa;

        //WSJTX

        //Windows Size
        if (windowSize.length()>0)
        {
            stream << "MainWindowSize=" << windowSize << ";" <<  QT_ENDL;
        }
        if (latestBackup.length()>0)
        {
            stream << "LatestBackup=" << latestBackup << ";";
        }
        file.close ();
    hamlibPage->stopHamlib();
    //qDebug() << "SetupDialog::slotOkButtonClicked - just before leaving";
    QDialog::accept();
    logEvent(Q_FUNC_INFO, "END", Debug);
    //qDebug() << "SetupDialog::slotOkButtonClicked - END";
    //close();
}

void SetupDialog::slotReadConfigData()
{
    //qDebug() << "SetupDialog::slotReadConfigData";
    logEvent(Q_FUNC_INFO, "Start", Debug);
    if (firstTime)
    {
        //qDebug() << "SetupDialog::slotReadConfigData - First time";
        setDefaults();
        bands.removeDuplicates();
        modes.removeDuplicates();
        logViewFields.removeDuplicates();
        bandModePage->setActiveModes(modes);
        bandModePage->setActiveBands(bands);
        logViewPage->setActiveFields(logViewFields);
    }

    //qDebug() << "SetupDialog::slotReadConfigData - 1";

    QFile file(configFileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))  /* Flawfinder: ignore */
    {
        //qDebug() << "SetupDialog::slotReadConfigData() File not found" << configFileName;
        //firstTime = true;
        emit debugLog (Q_FUNC_INFO, "END-1", logLevel);
        return;
    }
    //qDebug() << "SetupDialog::slotReadConfigData - 2";
    //dxClusterServers.clear();

    while (!file.atEnd()){
        QByteArray line = file.readLine();
        processConfigLine(line);
        //qDebug() << "SetupDialog::slotReadConfigData - in the while";
    }
    //qDebug() << "SetupDialog::slotReadConfigData - 3";

    dxClusterPage->setDxclusterServersComboBox(dxClusterServers);
    dxClusterPage->setSelectedDxClusterServer(dxClusterServerToUse);

    if (modes.isEmpty())
    {
        modes << "SSB" << "CW" << "RTTY";
    }
    if (bands.isEmpty())
    {
        bands << "10M" << "12M" << "15M" << "17M" << "20M" << "40M" << "80M" << "160M";
    }
    if (logViewFields.isEmpty())
    {
        logViewFields << "qso_date" << "call" << "rst_sent" << "rst_rcvd" << "bandid" << "modeid" << "comment";
    }
    modes.removeDuplicates();
    bandModePage->setActiveModes(modes);
    bands.removeDuplicates();
    bandModePage->setActiveBands(bands);
    logViewFields.removeDuplicates();
    logViewPage->setActiveFields(logViewFields);
    //qDebug() << "SetupDialog::slotReadConfigData - END";
    logEvent(Q_FUNC_INFO, "END", Debug);
}

bool SetupDialog::processConfigLine(const QString &_line)
{
    //qDebug() << "SetupDialog::processConfigLine: " << _line;
    logEvent(Q_FUNC_INFO, "Start", Debug);

    QString line = _line.simplified();
    //line.simplified();
    int i = 0; //aux variable
    QStringList values = line.split("=", QT_SKIP);
    QString tab = QString();

    if (line.startsWith('#')){
           //qDebug() << "SetupDialog::processConfigLine: Comment Line!";
        emit debugLog (Q_FUNC_INFO, "END-1", logLevel);
        return true;
    }
    if (!( (line.contains('=')) && (line.contains(';')))){
           //qDebug() << "SetupDialog::processConfigLine: Wrong Line!";
        emit debugLog (Q_FUNC_INFO, "END-2", logLevel);
        return false;
    }
    QString value = values.at(1);
    tab = (values.at(0)).toUpper();

    int endValue = value.indexOf(';');
    if (endValue>-1)
    {
        value = value.left(value.length() - (value.length() - endValue));
    }
    value = checkAndFixASCIIinADIF(value); // Check whether the value is valid.
      //qDebug() << "SetupDialog::processConfigLine: TAB: " << tab;
      //qDebug() << "SetupDialog::processConfigLine: VALUE: " << value;
    if (tab == "CALLSIGN"){
           //qDebug() << "SetupDialog::processConfigLine: CALLSIGN: " << value;
        userDataPage->setMainCallsign(value);
    }else if (tab == "OPERATORS"){
        userDataPage->setOperators(value);
    }else if (tab=="CQZ"){
        userDataPage->setCQz((value).toInt());
    }else if (tab=="ITUZ"){
        userDataPage->setITUz((value).toInt());
    }else if (tab=="CONTEST"){
        //userDataPage->setContest(value);
    }else if (tab=="MODES"){
        readActiveModes(value);
        modes.removeDuplicates();
        bandModePage->setActiveModes(modes);
    }else if (tab=="BANDS"){
        readActiveBands(value);
        bands.removeDuplicates();
        bandModePage->setActiveBands(bands);
    //}else if (tab=="INMEMORY"){
    //    miscPage->setInMemory(value);
    }else if (tab=="LOGVIEWFIELDS"){
        logViewFields.clear();
        //qDebug() << Q_FUNC_INFO << ": " << value;
        //qDebug() << Q_FUNC_INFO << "llamando a filterValidFields";
        logViewFields << dataProxy->filterValidFields(value.split(",", QT_SKIP));
        logViewFields.removeDuplicates();
        logViewPage->setActiveFields(logViewFields);
    }else if (tab=="REALTIME"){
        miscPage->setRealTime(value);
    }else if (tab=="SHOWSECONDS"){
        miscPage->setShowSeconds (util->trueOrFalse (value));
    }else if (tab=="UTCTIME"){
        miscPage->setUTCTime(value);
    }else if (tab=="ALWAYSADIF"){
        miscPage->setAlwaysADIF(value);
    }else if (tab=="USEDEFAULTNAME"){
        miscPage->setDefaultFileName(value);
    }else if (tab=="DBPATH"){
        miscPage->setUseDefaultDBPath(value);
    }else if (tab=="DEFAULTADIFFILE"){
        miscPage->setDefaultFileName(value);
           //qDebug() << "SetupDialog::processConfigLine: FILE: " << value;
    }else if (tab=="IMPERIALSYSTEM"){
        miscPage->setImperial(value.toUpper());
    }else if (tab=="COMPLETEWITHPREVIOUS"){
        miscPage->setCompleteWithPrevious(value.toUpper());
    }else if (tab=="SENDQSLWHENREC"){
        miscPage->setSendQSLWhenRec(value.toUpper());
    }else if (tab=="MANAGEDXMARATHON"){
        miscPage->setDXMarathon(value.toUpper());
    }else if (tab=="DEBUGLOG"){
        miscPage->setDebugLogLevel(value);
    }
    else if (tab=="SHOWCALLSIGNINSEARCH"){
        miscPage->setShowStationCallSignInSearch(value.toUpper());
    }
    else if (tab=="CHECKNEWVERSIONS"){
        miscPage->setCheckNewVersions(value);
    }
    else if (tab=="PROVIDEINFO"){
        miscPage->setReportInfo(value);
    }
    /*
    else if (tab=="LOGSORT"){
        miscPage->setLogSort(value);
    }
    */
    else if (tab=="SENDEQSLBYDEFAULT"){
        miscPage->setSetEQSLByDefault(value);
    }
    else if (tab=="DUPLICATEDQSOSLOT"){
        if (value.toInt()>=0)
        {
            miscPage->setDupeTime(value.toInt());
        }
    }
    else if (tab == "CHECKVALIDCALLS")
    {
        miscPage->setCheckCalls (util->trueOrFalse (value));
    }
    /*
    else if (tab=="PSTROTATORACTIVE"){
        interfacesWindowsPage->setSendToPSTRotator(value);
    }
    else if (tab=="PSTROTATORPORT"){
        interfacesWindowsPage->setPSTRotatorUDPServerPort(value);
    }
    else if (tab=="PSTROTATORSERVER")
    {
        interfacesWindowsPage->setPSTRotatorUDPServer(value);
    }
    */
    else if (tab=="UDPSERVER"){
        UDPPage->setUDPServer(value);
    }
    else if (tab=="UDPNETWORKINTERFACE"){
        UDPPage->setNetworkInterface(value);
    }
    else if (tab=="UDPSERVERPORT"){
        UDPPage->setUDPServerPort(value);
    }
    else if (tab=="LOGFROMWSJTX")
    {
        UDPPage->setLogFromWSJTx(value);
    }
    else if (tab=="LOGAUTOFROMWSJTX")
    {
        UDPPage->setAutoLogFromWSJTx(value);
    }
    else if (tab=="REALTIMEFROMWSJTX")
    {
        UDPPage->setReaDataFromWSJTx(value);
    }
    else if (tab=="INFOTIMEOUT")
    {
        UDPPage->setTimeout(value);
    }
    else if (tab =="NAME")
    {
        userDataPage->setName(value);
    }
    else if (tab =="ADDRESS1")
    {
        userDataPage->setAddress1(value);
    }
    else if (tab =="ADDRESS2")
    {
        userDataPage->setAddress2(value);
    }
    else if (tab =="ADDRESS3")
    {
        userDataPage->setAddress3(value);
    }
    else if (tab =="ADDRESS4")
    {
        userDataPage->setAddress4(value);
    }
    else if (tab =="CITY")
    {
        userDataPage->setCity(value);
    }
    else if (tab =="ZIPCODE")
    {
        userDataPage->setZipCode(value);
    }
    else if (tab =="PROVINCESTATE")
    {
        userDataPage->setProvince(value);
    }
    else if (tab =="COUNTRY")
    {
        userDataPage->setCountry(value);
    }
    else if (tab =="POWER")
    {
        userDataPage->setPower(value);
    }
    else if (tab =="RIG1")
    {
        userDataPage->setRig1(value);
    }
    else if (tab =="RIG2")
    {
        userDataPage->setRig2(value);
    }
    else if (tab =="RIG3")
    {
        userDataPage->setRig3(value);
    }

    else if (tab =="ANTENNA1")
    {
        userDataPage->setAntenna1(value);
    }
    else if (tab =="ANTENNA2")
    {
        userDataPage->setAntenna2(value);
    }
    else if (tab =="ANTENNA3")
    {
        userDataPage->setAntenna3(value);
    }
    else if (tab =="STATIONLOCATOR")
    {
        if ( locator->isValidLocator(value) )
        {
            userDataPage->setStationLocator(value);
        }
    }else if (tab =="DXCLUSTERSHOWHF"){
        dxClusterPage->setShowHFQCheckbox(value);
    }else if (tab =="DXCLUSTERSHOWVHF"){
        dxClusterPage->setShowVHFQCheckbox(value);
    }else if (tab =="DXCLUSTERSHOWWARC"){
        dxClusterPage->setShowWARCQCheckbox(value);
    }else if (tab =="DXCLUSTERSHOWWORKED"){
        dxClusterPage->setShowWorkedQCheckbox(value);
    }else if (tab =="DXCLUSTERSHOWCONFIRMED"){
        dxClusterPage->setShowConfirmedQCheckbox(value);
    }else if (tab =="DXCLUSTERSHOWANN"){
        dxClusterPage->setShowANNQCheckbox(value);
    }else if (tab =="DXCLUSTERSHOWWWV"){
        dxClusterPage->setShowWWVQCheckbox(value);
    }else if (tab =="DXCLUSTERSHOWWCY"){
        dxClusterPage->setShowWCYQCheckbox(value);
    }else if(tab =="DXCLUSTERSERVERPORT"){
        dxClusterServers << value;
           //qDebug() << "SetupDialog::processConfigLine: dxClusterServers: " << dxClusterServers.last();
    }else if (tab  =="DXCLUSTERSERVERTOUSE"){
        dxClusterServerToUse=value;
    }
    else if (tab  =="DXCLUSTERSAVE"){
        dxClusterPage->setSaveActivityQCheckbox(value);
    }
    else if (tab  =="DXCLUSTERSENDTOMAP"){
        dxClusterPage->setSendSpotstoMap(value);
    }
    else if(tab =="NEWONECOLOR"){
        colorsPage->setNewOneColor(value);
    }else if(tab =="NEEDEDCOLOR"){
        colorsPage->setNeededColor(value);
    }else if(tab =="WORKEDCOLOR"){
        colorsPage->setWorkedColor(value);
    }else if(tab =="CONFIRMEDCOLOR"){
        colorsPage->setConfirmedColor(value);
    }else if(tab =="DEFAULTCOLOR"){
        colorsPage->setDefaultColor(value);
          //qDebug() << "SetupDialog::processConfigLine: DEFAULTCOLOR: " << value;
    }else if(tab =="DARKMODE"){
        colorsPage->setDarkMode(value);
    }else if(tab =="HAMLIBRIGTYPE"){
          //qDebug() << "SetupDialog::processConfigLine: Before HAMLIBRIGTYPE: " << value;
        hamlibPage->setRigType(value);
          //qDebug() << "SetupDialog::processConfigLine: After HAMLIBRIGTYPE: " << value;
    }else if(tab =="HAMLIBSERIALPORT"){
          //qDebug() << "SetupDialog::processConfigLine: HAMLIBSERIALPORT: " << value;
        hamlibPage->setSerialPort(value);
    }else if(tab =="HAMLIBSERIALBAUDS"){
          //qDebug() << "SetupDialog::processConfigLine: HAMLIBSERIALBAUDS: " << value;
        hamlibPage->setSerialSpeed(value.toInt());
    }else if(tab =="HAMLIB"){
          //qDebug() << "SetupDialog::processConfigLine: HAMLIB: " << value;
        hamlibPage->setActive(value);
    }else if(tab=="HAMLIBREADONLY"){
        hamlibPage->setReadOnly(value);
    }else if(tab =="HAMLIBSERIALDATABITS"){
        //qDebug() << "SetupDialog::processConfigLine: HAMLIBSERIALDATABITS: " << value;
        hamlibPage->setDataBits(value.toInt ());
    }else if(tab =="HAMLIBSERIALSTOPBITS"){
          //qDebug() << "SetupDialog::processConfigLine: HAMLIBSERIALSTOPBITS: " << value;
        hamlibPage->setStopBits(value);
    }else if(tab =="HAMLIBSERIALFLOWCONTROL"){
          //qDebug() << "SetupDialog::processConfigLine: HAMLIBSERIALFLOWCONTROL: " << value;
        hamlibPage->setFlowControl(value);
    }else if(tab =="HAMLIBSERIALPARITY"){
          //qDebug() << "SetupDialog::processConfigLine: HAMLIBSERIALPARITY: " << value;
        hamlibPage->setParity(value);
    }else if(tab =="HAMLIBSERIALRTS"){
          //qDebug() << "SetupDialog::processConfigLine: HAMLIBSERIALRTS: " << value;
        //hamlibPage->setRTS(value);
    }else if(tab =="HAMLIBSERIALDTR"){
          //qDebug() << "SetupDialog::processConfigLine: HAMLIBSERIALDTR: " << value;
        //hamlibPage->setDTR(value);
    }else if (tab == "HAMLIBRIGPOLLRATE"){
        hamlibPage->setPollingInterval(value.toInt());
    }else if (tab == "HAMLIBNETADDRESS"){
        hamlibPage->setRadioNetworkAddress (value);
    }else if (tab == "HAMLIBNETPORT"){
        hamlibPage->setRadioNetworkPort (value.toInt ());
    }else if(tab =="SELECTEDLOG"){
           //qDebug() << "SetupDialog::processConfigLine: SELECTEDLOG: " << value;
        i = value.toInt();

        if (dataProxy->doesThisLogExist(i))
        {
               //qDebug() << "SetupDialog::processConfigLine: dataProxy->doesThisLogExist TRUE";
        }
        else
        {
               //qDebug() << "SetupDialog::processConfigLine: dataProxy->doesThisLogExist FALSE";
            i = 0;
            while(!dataProxy->doesThisLogExist(i))
            {
                i++;
            }
        }
        logsPage->setSelectedLog(i);
           //qDebug() << "SetupDialog::processConfigLine: dataProxy->doesThisLogExist END";
    }else if(tab =="CLUBLOGACTIVE"){
        eLogPage->setClubLogActive(util->trueOrFalse(value));
    }
    else if(tab =="CLUBLOGREALTIME"){
        //clubLogPage->setClubLogRealTime(value);
        eLogPage->setClubLogRealTime(util->trueOrFalse(value));
    }
    else if(tab =="CLUBLOGPASS"){
        //clubLogPage->setPassword(value);
        eLogPage->setClubLogPassword(value);
    }
    else if(tab =="CLUBLOGEMAIL"){
        //clubLogPage->setEmail(value);
        eLogPage->setClubLogEmail(value);
    }
    else if(tab =="EQSLACTIVE"){
        //eQSLPage->setActive(value);
        eLogPage->setEQSLActive(util->trueOrFalse(value));
    }
    else if(tab =="EQSLCALL"){
        //eQSLPage->setCallsign(value);
        eLogPage->setEQSLUser(value);
    }
    else if(tab =="EQSLPASS"){
        //eQSLPage->setPassword(value);
        eLogPage->setEQSLPassword(value);
    }
    else if(tab =="QRZCOMACTIVE"){
        //eQSLPage->setActive(value);
        eLogPage->setQRZCOMActive(util->trueOrFalse(value));
    }
    else if(tab =="QRZCOMSUBSCRIBER"){
        eLogPage->setQRZCOMSubscriber(util->trueOrFalse (value));
    }
    else if(tab =="QRZCOMUSER"){
        eLogPage->setQRZCOMUser(value);
    }
    else if(tab =="QRZCOMAUTO"){
        eLogPage->setQRZCOMAutoCheck(util->trueOrFalse(value));
    }
    else if(tab =="QRZCOMPASS"){
        eLogPage->setQRZCOMPassword(value);
    }
    else if(tab =="QRZCOMLOGBOOKKEY"){
        eLogPage->setQRZCOMLogBookKEY(value);
    }
    else if(tab =="LOTWACTIVE"){
        eLogPage->setLoTWActive(util->trueOrFalse(value));
    }
    else if(tab =="LOTWPATH"){
        eLogPage->setTQSLPath(value);
    }
    else if(tab =="LOTWUSER"){
        eLogPage->setLoTWUser(value);
    }
    else if(tab =="LOTWPASS"){
        eLogPage->setLoTWPass(value);
    }
    else if(tab =="MAINWINDOWSIZE"){
        QStringList values;
        values.clear();
        values << value.split("x");
        if ((values.at(0).toInt()>0) && (values.at(1).toInt()>0))
        {
            windowSize = value;
        }
    }
    else if(tab =="DELETEALWAYSADIFILE"){
            miscPage->setDeleteAlwaysAdiFile(util->trueOrFalse(value));
        }
    else if (tab == "LATESTBACKUP"){
        if (value.length()>0)
        {
            latestBackup = value;
        }
        else
        {
            latestBackup = QString();
        }
    //s.append("LatestBackup=" + (QDateTime::currentDateTime()).toString("yyyyMMdd-hhmmss") + ";\n" );
    }
    else
    {
           //qDebug() << "SetupDialog::processConfigLine: NONE: ";
    }

    // Lines are: Option = value;

       //qDebug() << "SetupDialog::processConfigLine: END " ;
    logEvent(Q_FUNC_INFO, "END", Debug);
    return true;
}

void SetupDialog::readActiveBands (const QString &actives)
{ // Checks a "10m, 12m" QString, checks if  they are valid bands and import to the
    // bands used in the program
      //qDebug() << "SetupDialog::readActiveBands: " << actives;

    logEvent(Q_FUNC_INFO, "Start", Debug);
    bool atLeastOne = false;

    QStringList values = actives.split(", ", QT_SKIP);
    QStringList _abands;

    for (int i = 0; i < values.size() ; i++)
    {
        if (isValidBand(values.at(i)))
        {
            if (!atLeastOne)
            {
                   //qDebug() << "SetupDialog::readActiveBands (at least One!): " << values.at(i);
                atLeastOne = true;
                _abands.clear();
            }

            _abands << values.at(i);
               //qDebug() << "SetupDialog::readActiveBands: " << values.at(i);
        }
    }

    bands.clear();
    //_abands.removeDuplicates();

    bands << dataProxy->getBandsInLog(-1);
    bands << _abands;
    bands.removeDuplicates();
    //qDebug() << Q_FUNC_INFO << " - END";
    logEvent(Q_FUNC_INFO, "END", Debug);
}

void SetupDialog::readActiveModes (const QString &actives)
{
       //qDebug() << "SetupDialog::readActiveModes: " << actives;
    logEvent(Q_FUNC_INFO, "Start", Debug);

    bool atLeastOne = false;
    QStringList _amodes;//, _backModes;
    // _backModes.clear();
    // _backModes << modes;
    QStringList values = actives.split(", ", QT_SKIP);
    values.removeDuplicates();

    for (int i = 0; i < values.size() ; i++)
    {
        if (isValidMode(values.at(i)))
        {
            if (!atLeastOne)
            {
                atLeastOne = true;
                _amodes.clear();
            }
            _amodes << values.at(i);
        }
    }

    modes.clear();
    modes = dataProxy->getModesInLog(-1);
    modes << _amodes;
    modes.removeDuplicates();
    logEvent(Q_FUNC_INFO, "END", Debug);
       //qDebug() << "SetupDialog::readActiveModes: " << modes.join(" / ");
}

bool SetupDialog::isValidBand (const QString &b)
{
       //qDebug() << "SetupDialog::isValidBand: "<< b;
    logEvent(Q_FUNC_INFO, "Start", Debug);
    QString stringQuery = QString("SELECT id FROM band WHERE name='%1'").arg(b);
    QSqlQuery query(stringQuery);
    query.next();
    logEvent(Q_FUNC_INFO, "END", Debug);
    return query.isValid();
}
bool SetupDialog::isValidMode (const QString &b)
{
       //qDebug() << "SetupDialog::isValidMode: " << b;
    logEvent(Q_FUNC_INFO, "Start", Debug);
    QString stringQuery = QString("SELECT id FROM mode WHERE name='%1'").arg(b);
    QSqlQuery query(stringQuery);
    query.next();
    logEvent(Q_FUNC_INFO, "END", Debug);
    return query.isValid();
}

void SetupDialog::setDefaults()
{
       //qDebug() << "SetupDialog::setDefaults";
    logEvent(Q_FUNC_INFO, "Start", Debug);
    miscPage->setRealTime("TRUE");
    miscPage->setUTCTime("TRUE");
    miscPage->setImperial("FALSE"); //Metric system is the default
    miscPage->setAlwaysADIF("FALSE");
    miscPage->setSendQSLWhenRec("TRUE");
    miscPage->setShowStationCallSignInSearch("TRUE");
    miscPage->setCheckNewVersions("TRUE");
    miscPage->setReportInfo("FALSE");
    miscPage->setDXMarathon("FALSE");
    miscPage->setDebugLogLevel(util->getDebugLevels().at(0));
    //miscPage->setLogSort("FALSE");
    miscPage->setSetEQSLByDefault("TRUE");
    miscPage->setCheckCalls (true);

    UDPPage->setUDPServer("FALSE");
    UDPPage->setUDPServerPort("2237");
    UDPPage->setTimeout("2000");
    UDPPage->setLogFromWSJTx("FALSE");
    UDPPage->setReaDataFromWSJTx("FALSE");
    UDPPage->setAutoLogFromWSJTx("FALSE");
    //interfacesWindowsPage->setSendToPSTRotator("FALSE");
    //interfacesWindowsPage->setPSTRotatorUDPServer("locahost");
    //interfacesWindowsPage->setPSTRotatorUDPServerPort("12040");

    dxClusterPage->setShowHFQCheckbox("TRUE");
    dxClusterPage->setShowVHFQCheckbox("TRUE");
    dxClusterPage->setShowWARCQCheckbox("TRUE");
    dxClusterPage->setShowWorkedQCheckbox("TRUE");
    dxClusterPage->setShowConfirmedQCheckbox("TRUE");
    dxClusterPage->setShowANNQCheckbox("TRUE");
    dxClusterPage->setShowWWVQCheckbox("TRUE");
    dxClusterPage->setShowWCYQCheckbox("TRUE");
    dxClusterServers.clear();
    dxClusterServers.append("dxfun.com:8000");
    dxClusterServerToUse = "dxfun.com:8000";

    if (modes.isEmpty())
    {
        modes << "SSB" << "CW" << "RTTY";
        modes.removeDuplicates();
    }

    if (bands.isEmpty())
    {
        bands << "10M" << "12M" << "15M" << "17M" << "20M" << "40M" << "80M" << "160M";
        bands.removeDuplicates();
    }
    logEvent(Q_FUNC_INFO, "END", Debug);
}

QString SetupDialog::checkAndFixASCIIinADIF(const QString &_data)
{
       //qDebug() << "SetupDialog::checkAndFixASCIIinADIF " << _data;
//TODO: this function is also in the FileManager class. Maybe I should call that one and keep just one copy
    logEvent(Q_FUNC_INFO, "Start", Debug);
    ushort unicodeVal;
    QString st = _data;
    QString newString;
    newString.clear();
    for(int i=0; i < st.length(); i++)
    {
    // Get unicode VALUE into unicodeVal
        unicodeVal = (st.at(i)).unicode();
        if ((20 <= unicodeVal ) && (unicodeVal <= 126))
        {
            newString.append(st.at(i));
        }
           //qDebug() << "SetupDialog::checkAndFixunicodeinADIF: " << st.at(i) <<" = " << QString::number(unicodeVal);
    }

    // Show into another lineEdit

    logEvent(Q_FUNC_INFO, "END", Debug);
    return newString;
}

bool SetupDialog::haveAtleastOneLog()
{
    logEvent(Q_FUNC_INFO, "Start", Debug);
    emit debugLog (Q_FUNC_INFO, "END-1", logLevel);
    return dataProxy->haveAtLeastOneLog();
    //logEvent(Q_FUNC_INFO, "END", Debug);
}

void SetupDialog::setClubLogActive(const bool _b)
{
    logEvent(Q_FUNC_INFO, "Start", Debug);
    eLogPage->setClubLogActive(_b);
    logEvent(Q_FUNC_INFO, "END", Debug);
}

void SetupDialog::setQRZCOMAutoCheckActive(const bool _b)
{
     eLogPage->setQRZCOMAutoCheck(_b);
}

void SetupDialog::setEQSLActive(const bool _b)
{
    eLogPage->setEQSLActive(_b);
}

void SetupDialog::checkIfNewBandOrMode()
{
      //qDebug() << "SetupDialog::checkIfNewBandOrMode: logLevel: " << QString::number(logLevel);
    logEvent(Q_FUNC_INFO, "Start", Debug);
    QStringList _items;

    _items.clear();
       //qDebug() << "SetupDialog::checkIfNewBandOrMode -1";
    _items << dataProxy->getBandsInLog(-1);
       //qDebug() << "SetupDialog::checkIfNewBandOrMode -2";
    _items << (bandModePage->getBands()).split(", ", QT_SKIP);
       //qDebug() << "SetupDialog::checkIfNewBandOrMode -3";
    _items.removeDuplicates();
       //qDebug() << "SetupDialog::checkIfNewBandOrMode -4";
    bandModePage->setActiveBands(_items);
       //qDebug() << "SetupDialog::checkIfNewBandOrMode -5";

    _items.clear();
    _items << dataProxy->getModesInLog(-1);
    _items << (bandModePage->getModes()).split(", ", QT_SKIP);
    _items.removeDuplicates();
    bandModePage->setActiveModes(_items);
    logEvent(Q_FUNC_INFO, "END", Debug);
       //qDebug() << "SetupDialog::checkIfNewBandOrMode END";
}


void SetupDialog::slotAnalyzeNewLogData(const QStringList _qs)
{
      //qDebug() << "SetupDialog::slotAnalyzeNewLogData (length=" << QString::number(_qs.length()) << ")";
       //qDebug() << "SetupDialog::slotAnalyzeNewLogData";
 // We receive the station callsign and operators from the logs tab
    logEvent(Q_FUNC_INFO, "Start", Debug);
    if (_qs.length()!=2)
    {
        emit debugLog (Q_FUNC_INFO, "END-1", logLevel);
        return;
    }
    userDataPage->setMainCallsign(_qs.at(0));
    userDataPage->setOperators(_qs.at(1));
    logEvent(Q_FUNC_INFO, "END", Debug);
}

void SetupDialog::slotSetStationCallSign(const QString &_p)
{
       //qDebug() << "SetupDialog::slotSetStationCallSign: " << _p;
    logEvent(Q_FUNC_INFO, "Start", Debug);
    logsPage->setDefaultStationCallsign(_p);
    logEvent(Q_FUNC_INFO, "END", Debug);
}

void SetupDialog::slotSetOperators(const QString &_p)
{
       //qDebug() << "SetupDialog::slotSetOperators: " << _p;
    logEvent(Q_FUNC_INFO, "Start", Debug);
    logsPage->setDefaultOperators(_p);
    logEvent(Q_FUNC_INFO, "END", Debug);
}

void SetupDialog::setLogLevel(const DebugLogLevel _sev)
{
    logLevel = _sev;
    miscPage->setDebugLogLevel(util->debugLevelToString(_sev));
}

void SetupDialog::slotQueryErrorManagement(QString functionFailed, QString errorCodeS, QString nativeError, QString failedQuery)
{   logEvent(Q_FUNC_INFO, "Start", Debug);
    emit queryError(functionFailed, errorCodeS, nativeError, failedQuery);
    logEvent(Q_FUNC_INFO, "END", Debug);
}

void SetupDialog::slotFocusOK()
{
    okButton->setFocus(Qt::OtherFocusReason);
}

void SetupDialog::showEvent(QShowEvent *event)
{
    //qDebug() << Q_FUNC_INFO;
    //qDebug() << Q_FUNC_INFO << " - selectedLog: " << QString::number(logsPage->getSelectedLog());
    QWidget::showEvent(event);
    userDataPage->setStationFocus();
}

void SetupDialog::logEvent(const QString &_func, const QString &_msg,  DebugLogLevel _level)
{
    if (logLevel<=_level)
        emit debugLog (_func, _msg, _level);
}
