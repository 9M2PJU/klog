/***************************************************************************
                          adiflotwexportwidget.cpp  -  description
                             -------------------
    begin                : July 2020
    copyright            : (C) 2020 by Jaime Robles
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
#include "adiflotwexportwidget.h"


AdifLoTWExportWidget::AdifLoTWExportWidget(DataProxy_SQLite *dp, const QString &_parentFunction, QWidget *parent) : QWidget(parent)
{
#ifdef QT_DEBUG
  //qDebug() << ": " << _parentFunction;
#else
#endif
    //qDebug() << Q_FUNC_INFO << " - Start: " + _parentFunction;
    dataProxy = dp;
    starting = true;
    util = new Utilities(Q_FUNC_INFO);
    util->setLongPrefixes(dataProxy->getLongPrefixes());
    util->setSpecialCalls(dataProxy->getSpecialCallsigns());
    stationCallsignComboBox = new QComboBox;
    myGridSquareComboBox = new QComboBox;
    startDate = new QDateEdit;
    endDate = new QDateEdit;
    okButton = new QPushButton;
    cancelButton = new QPushButton;
    tableWidget = new QTableWidget;
    topLabel = new QLabel;
    numberLabel = new QLabel;
    selectedEMode = ModeLotW;   //By default this widget will be used for LoTW Export.
    defaultStationCallsign = QString();
    defaultMyGrid = QString();
    util->setLongPrefixes(dataProxy->getLongPrefixes());
    util->setSpecialCalls(dataProxy->getSpecialCallsigns());
    createUI();
    starting = false;
    //qDebug() << Q_FUNC_INFO << " - END";
}
AdifLoTWExportWidget::~AdifLoTWExportWidget()
{
    delete(util) ;
}

void AdifLoTWExportWidget::setDefaultStationCallsign(const QString &_st)
{
    //qDebug() << Q_FUNC_INFO << " - Start";
    if (util->isValidCall(_st))
    {
        defaultStationCallsign = _st;
    }
    //qDebug() << Q_FUNC_INFO << " - END";
}

void AdifLoTWExportWidget::setDefaultMyGrid(const QString &_st)
{
    //qDebug() << Q_FUNC_INFO << " - Start";
    if (util->isValidGrid(_st))
    {
        defaultMyGrid = _st;
    }
    //qDebug() << Q_FUNC_INFO << " - END";
}

void AdifLoTWExportWidget::createUI()
{
    //qDebug() << Q_FUNC_INFO << " - Start";
    //fillStationCallsignComboBox();
    tableWidget->setSortingEnabled (true);
    stationCallsignComboBox->setToolTip(tr("Select the Station Callsign that you want to use to upload the log."));

    startDate->clear();
    startDate->setToolTip(tr("Select the start date to export the QSOs. The default date is the date of the first QSO with this station callsign."));

    endDate->clear();

    //endDate->setDate(QDate::currentDate());
    endDate->setToolTip(tr("Select the end date to export the QSOs. The default date is the date of the last QSO with this station callsign."));

    QLabel *stationLabel = new QLabel;
    stationLabel->setText(tr("Station callsign"));

    QLabel *myGridLabel = new QLabel;
    myGridLabel->setText(tr("My Locator"));

    QLabel *startLabel = new QLabel;
    startLabel->setText(tr("Start date"));

    QLabel *endLabel = new QLabel;
    endLabel->setText(tr("End date"));

    okButton->setText(tr("Ok"));
    cancelButton->setText(tr("Cancel"));

    hv = tableWidget->verticalHeader();
    hv->hide();
    hv->setStretchLastSection(true);
    hh = tableWidget->horizontalHeader();

    QStringList header;
    header.clear();
    header << tr("DX") << tr("Date/Time") << tr("Band") << tr("Mode");
    tableWidget->setColumnCount(header.length());
    tableWidget->setHorizontalHeaderLabels(header);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(topLabel, 0, 0, 1, -1);
    mainLayout->addWidget(stationLabel, 1, 0);
    mainLayout->addWidget(stationCallsignComboBox, 2, 0);

    mainLayout->addWidget(myGridLabel, 1, 1);
    mainLayout->addWidget(myGridSquareComboBox, 2, 1);

    mainLayout->addWidget(startLabel, 1, 2);
    mainLayout->addWidget(startDate, 2, 2);
    mainLayout->addWidget(endLabel, 1, 3);
    mainLayout->addWidget(endDate, 2, 3);
    mainLayout->addWidget(tableWidget, 3, 0, 1, -1);
    mainLayout->addWidget(numberLabel, 4, 0);
    mainLayout->addWidget(okButton, 4, 1);
    mainLayout->addWidget(cancelButton, 4, 2);

    setLayout(mainLayout);
    connect(startDate, SIGNAL(dateChanged(QDate)), this, SLOT(slotDateChanged())) ;
    connect(endDate, SIGNAL(dateChanged(QDate)), this, SLOT(slotDateChanged() ));
    connect(stationCallsignComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotStationCallsignChanged() ) ) ;
    connect(myGridSquareComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotMyGridChanged() ) ) ;
    connect(okButton, SIGNAL(clicked()), this, SLOT(slotOKPushButtonClicked() ) );
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(slotCancelPushButtonClicked() ) );
    //qDebug() << Q_FUNC_INFO << " - END";
}


void AdifLoTWExportWidget::setDefaultStationComboBox()
{
    //qDebug() << Q_FUNC_INFO << " - Start";
    //stationCallsignComboBox->blockSignals(true);
    if (!util->isValidCall(defaultStationCallsign))
    {
        //qDebug() << Q_FUNC_INFO << " - END-1";
        //stationCallsignComboBox->blockSignals(false);
        return;
    }
    if (stationCallsignComboBox->findText(defaultStationCallsign, Qt::MatchCaseSensitive) >= 0)
    {
       stationCallsignComboBox->setCurrentIndex(stationCallsignComboBox->findText(defaultStationCallsign, Qt::MatchCaseSensitive));
    }
    //stationCallsignComboBox->blockSignals(false);
    //qDebug() << Q_FUNC_INFO << " - END";
}

void AdifLoTWExportWidget::setDefaultMyGridComboBox()
{
    //qDebug() << Q_FUNC_INFO << " - Start";
    if (!util->isValidGrid(defaultMyGrid))
    {
        //qDebug() << Q_FUNC_INFO << " - END-1";
        return;
    }
    if (myGridSquareComboBox->findText(defaultMyGrid, Qt::MatchCaseSensitive) >= 0)
    {
       myGridSquareComboBox->setCurrentIndex(myGridSquareComboBox->findText(defaultMyGrid, Qt::MatchCaseSensitive));
       //qDebug() << Q_FUNC_INFO << ": 1: " << myGridSquareComboBox->currentText();
    }
    else if (myGridSquareComboBox->count()>=3)
    {
       myGridSquareComboBox->findText(myGridSquareComboBox->itemText(2), Qt::MatchCaseSensitive);
       //qDebug() << Q_FUNC_INFO << ": 2:  " << myGridSquareComboBox->currentText();
    }
    else
    {
        //qDebug() << Q_FUNC_INFO << ": 3";
    }
    //qDebug() << Q_FUNC_INFO << " - END";
}

void AdifLoTWExportWidget::fillStationCallsignComboBox()
{
    //qDebug() << Q_FUNC_INFO << " - Start";
    //stationCallsignComboBox->blockSignals(true);
    stationCallsignComboBox->clear();
    //qDebug() << Q_FUNC_INFO << " -1" ;
    stationCallsignComboBox->addItem(tr("Not defined"));
    //qDebug() << Q_FUNC_INFO << " -2" ;
    if (currentExportMode == ModeADIF)
    {
        //qDebug() << Q_FUNC_INFO << " -3";
        stationCallsignComboBox->addItem(tr("ALL"));
        //qDebug() << Q_FUNC_INFO << " -4";
    }

    if (currentExportMode == ModeLotW)
    {
        //qDebug() << Q_FUNC_INFO << " -3";
        stationCallsignComboBox->addItems(dataProxy->getStationCallSignsFromLogWithLoTWPendingToSend(logNumber));
        //qDebug() << Q_FUNC_INFO << " -4";
    }
    else
    {
        //qDebug() << Q_FUNC_INFO << " -5";
        stationCallsignComboBox->addItems(dataProxy->getStationCallSignsFromLog(logNumber));
        //qDebug() << Q_FUNC_INFO << " -6";
    }
    //stationCallsignComboBox->blockSignals(false);
    //qDebug() << QString::number(stationCallsignComboBox->count());
    //qDebug() << Q_FUNC_INFO << " - END";
}

void AdifLoTWExportWidget::fillStationMyGridComboBox()
{
    //qDebug() << Q_FUNC_INFO << " - Start";
    // Keep the grid that is shown now
    // clean and fill the combo.
    // If the saved locator is in the list, it is selected.
    //myGridSquareComboBox->blockSignals(true);
    QString tempGrid = myGridSquareComboBox->currentText ();
    myGridSquareComboBox->clear();
    QStringList grids;
    grids.clear ();
    if (currentExportMode != ModeLotW)
    {
        myGridSquareComboBox->addItem(tr("Not defined"));
        myGridSquareComboBox->addItem(tr("ALL"));
        grids.append (dataProxy->getGridsToBeSent (stationCallsignComboBox->currentText(), startDate->date(), endDate->date(), false, logNumber));
    }
    else
    {
        grids.append (dataProxy->getGridsToBeSent (stationCallsignComboBox->currentText(), startDate->date(), endDate->date(), true, logNumber));
    }

    myGridSquareComboBox->addItems(grids);

    if (myGridSquareComboBox->findText(tempGrid, Qt::MatchCaseSensitive) >= 0)
    {
       myGridSquareComboBox->setCurrentIndex(myGridSquareComboBox->findText(tempGrid, Qt::MatchCaseSensitive));
    }
    //myGridSquareComboBox->blockSignals(false);
    //qDebug() << Q_FUNC_INFO << " - END";
}

void AdifLoTWExportWidget::setTopLabel(const QString &_t)
{
    //qDebug() << Q_FUNC_INFO << " - Start";
    topLabel->setText(_t);
    //qDebug() << Q_FUNC_INFO << " - END";
}

void AdifLoTWExportWidget::fillDates()
{
    // Shows the first and last QSO done with one specific callsign.
    //qDebug() << Q_FUNC_INFO << " - Start";
    //startDate->blockSignals(true);
    //endDate->blockSignals(true);

    startDate->setDate(dataProxy->getFirstQSODateFromCall(stationCallsignComboBox->currentText()));
    endDate->setDate(dataProxy->getLastQSODateFromCall(stationCallsignComboBox->currentText()));

    //startDate->blockSignals(false);
    //endDate->blockSignals(false);
    //qDebug() << Q_FUNC_INFO << " - END";
}

void AdifLoTWExportWidget::fillTable()
{
    //qDebug() << Q_FUNC_INFO << " - Start";

    QList<int> qsos;
    qsos.clear();
       bool justQueued = true;
       switch (currentExportMode)
       {
           case ModeADIF:
           justQueued = false;
           //qDebug() << Q_FUNC_INFO << " ADIF";

           break;
       case ModeLotW:
           //qDebug() << Q_FUNC_INFO << " LoTW";
           justQueued = true;

           break;
       case ModeClubLog:
           //qDebug() << Q_FUNC_INFO << " ClubLog";
           //justQueued = true;

           break;
       case ModeEQSL:
           //qDebug() << Q_FUNC_INFO << " EQSL";
           justQueued = true;
           break;
       case ModeQRZ:
           //qDebug() << Q_FUNC_INFO << " QRZ";
           justQueued = true;
           break;
       }

       if (stationCallsignComboBox->currentIndex() == 0)
       { // Not defined station_callsign (blank)
           //qDebug() << Q_FUNC_INFO << " blank station callsign ";
           qsos.append(dataProxy->getQSOsListLoTWToSend(QString(), myGridSquareComboBox->currentText(), startDate->date(), endDate->date(), justQueued, logNumber));
       }
       else if((stationCallsignComboBox->currentIndex() == 1) && (currentExportMode == ModeADIF))
       { // ALL stations, no matter the station.
           //qDebug() << Q_FUNC_INFO << " ALL station callsign ";
           qsos.append(dataProxy->getQSOsListLoTWToSend("ALL", myGridSquareComboBox->currentText (), startDate->date(), endDate->date(), justQueued, logNumber));
           //qsos.append(dataProxy->getQSOsListToBeExported(stationCallsignComboBox->currentText(), startDate->date(), endDate->date()));
       }
       else
       {
           //qDebug() << Q_FUNC_INFO << " OTHER station callsign ";
           if (currentExportMode == ModeClubLog)
           {
               //qDebug() << Q_FUNC_INFO << " Mode ClubLog";
               qsos.append(dataProxy->getQSOsListClubLogToSent(stationCallsignComboBox->currentText(), startDate->date(), endDate->date(), true, logNumber));
           }
           else if (currentExportMode == ModeEQSL)
           {
              //qDebug() << Q_FUNC_INFO << " Mode eQSL";
              qsos.append(dataProxy->getQSOsListEQSLToSent(stationCallsignComboBox->currentText(), startDate->date(), endDate->date(), true));
           }
           else if (currentExportMode == ModeQRZ)
           {
              //qDebug() << Q_FUNC_INFO << " Mode QRZ";
              qsos.append(dataProxy->getQSOsListQRZCOMToSent(stationCallsignComboBox->currentText(), startDate->date(), endDate->date(), true));
           }
           else if (currentExportMode == ModeLotW)
           {
                //qDebug() << Q_FUNC_INFO << " Mode LoTW";
                qsos.append(dataProxy->getQSOsListLoTWToSend (stationCallsignComboBox->currentText(), myGridSquareComboBox->currentText (), startDate->date(), endDate->date(), true, logNumber));
           }
           else
           {//(currentExportMode == ModeADIF)
               //qDebug() << Q_FUNC_INFO << " Mode ELSE";
               qsos.append(dataProxy->getQSOsListToBeExported(stationCallsignComboBox->currentText(), myGridSquareComboBox->currentText(),  startDate->date(), endDate->date()));
           }
       }

       //qDebug() << Q_FUNC_INFO << " -3" ;
       tableWidget->clearContents();
       tableWidget->setRowCount(0);
       if (tableWidget->columnCount()>0)
       {
            //qDebug() << Q_FUNC_INFO << " pre FOR";
            for (int i=0; i<qsos.length(); i++)
            {
               //qDebug() << Q_FUNC_INFO << " in FOR " << QString::number(i);
               addQSO(qsos.at(i));
            }
       }

       numberLabel->setText(tr("QSOs: ") + QString::number(qsos.count()));
       if (qsos.count()>0)
       {
           //qDebug() << Q_FUNC_INFO << " Enable OKButton";
           okButton->setEnabled(true);
       }
       else
       {
           //qDebug() << Q_FUNC_INFO << " Disable OKButton";
           okButton->setEnabled(false);
       }
    //qDebug() << Q_FUNC_INFO << " - END";
}

void AdifLoTWExportWidget::addQSO(const int _qsoID)
{
    //qDebug() << "AdifLoTWExportWidget::addQSO: " << QString::number(_qsoID);

    //qDebug() << Q_FUNC_INFO << " - Start";
    QStringList qsoToAdd;
    qsoToAdd.clear();
    qsoToAdd << dataProxy->getQSODetailsForLoTWDownload(_qsoID);

    //qDebug() << "AdifLoTWExportWidget::addQSO: Columns: " << QString::number(tableWidget->columnCount());
    //qDebug() << "AdifLoTWExportWidget::addQSO: qsoToAdd-length: " << QString::number(qsoToAdd.length());

    if (qsoToAdd.length() == tableWidget->columnCount())
    {
        tableWidget->insertRow(tableWidget->rowCount());

        for (int i = 0; i<qsoToAdd.length(); i++)
        {
            //qDebug() << "AdifLoTWExportWidget::addQSO: qsoToAdd.at(i): " << qsoToAdd.at(i);
            QTableWidgetItem *newItemID = new QTableWidgetItem(qsoToAdd.at(i));
            newItemID->setTextAlignment(Qt::AlignCenter);
            newItemID->setFlags(Qt::NoItemFlags);
            tableWidget->setItem(tableWidget->rowCount()-1, i, newItemID);
        }
    }
    //qDebug() << Q_FUNC_INFO << " - END";
}

void AdifLoTWExportWidget::slotStationCallsignChanged()
{
    //qDebug() << Q_FUNC_INFO << " - Start";
    if (starting)
    {
        //qDebug() << Q_FUNC_INFO << " - END-1";
        return;
    }
    if (stationCallsignComboBox->count()<1)
    {
        //qDebug() << Q_FUNC_INFO << " - END-1";
        return;
    }
    //qDebug() << Q_FUNC_INFO << " - 01" ;
    fillDates();
    //qDebug() << Q_FUNC_INFO << " - 03" ;
    fillStationMyGridComboBox();
    updateIfNeeded();
    //qDebug() << Q_FUNC_INFO << " - END";
}

void AdifLoTWExportWidget::updateIfNeeded()
{
    if (currentCall != stationCallsignComboBox->currentText())
    {
        fillTable();
    }
    else if (currentGrid != myGridSquareComboBox->currentText())
    {
        fillTable();
    }
    else if (currentStart != startDate->date())
    {
        fillTable();
    }
    else if (currentEnd != endDate->date())
    {
        fillTable();
    }
}


void AdifLoTWExportWidget::slotMyGridChanged()
{
    //qDebug() << Q_FUNC_INFO << " - Start: " << myGridSquareComboBox->currentText();
    if (starting)
    {
        //qDebug() << Q_FUNC_INFO << " - END-1";
        return;
    }
    fillTable();
    //qDebug() << Q_FUNC_INFO << " - END";
}

void AdifLoTWExportWidget::slotDateChanged()
{
    //qDebug() << Q_FUNC_INFO << " - Start";
    if (starting)
    {
        //qDebug() << Q_FUNC_INFO << " - END-1";
        return;
    }
    updateIfNeeded();
    //qDebug() << Q_FUNC_INFO << " - END";
}

void AdifLoTWExportWidget::slotOKPushButtonClicked()
{
    //qDebug() << Q_FUNC_INFO << " - Start";
    this->hide();
    if (stationCallsignComboBox->currentIndex() == 0)
    {
        emit selection("NOT", myGridSquareComboBox->currentText(), startDate->date(), endDate->date(), currentExportMode);
    }
    else if (stationCallsignComboBox->currentIndex() == 1)
    {
        if ((currentExportMode == ModeLotW) || (currentExportMode == ModeClubLog) || (currentExportMode == ModeQRZ)|| (currentExportMode == ModeEQSL))
        {
            emit selection(stationCallsignComboBox->currentText(), myGridSquareComboBox->currentText(), startDate->date(), endDate->date(), currentExportMode);
        }
        else
        {
            emit selection("ALL", myGridSquareComboBox->currentText(), startDate->date(), endDate->date(), currentExportMode);
        }
    }
    else
    {
        emit selection(stationCallsignComboBox->currentText(), myGridSquareComboBox->currentText(), startDate->date(), endDate->date(), currentExportMode);
    }
    //qDebug() << "AdifLoTWExportWidget::slotOKPushButtonClicked - END";
    close();
    //qDebug() << Q_FUNC_INFO << " - END";
}

void AdifLoTWExportWidget::slotCancelPushButtonClicked()
{
     //qDebug() << Q_FUNC_INFO << " - Start";
     close();
     //qDebug() << Q_FUNC_INFO << " - END";
}

void AdifLoTWExportWidget::closeEvent(QCloseEvent *event)
{
    //qDebug() << Q_FUNC_INFO << " - Start";
    event->accept();
    //qDebug() << Q_FUNC_INFO << " - END";
}

void AdifLoTWExportWidget::showEvent(QShowEvent *event)
{
    //qDebug() << Q_FUNC_INFO << " - Start";
    starting = true;
    //myGridSquareComboBox->blockSignals(true);
    //stationCallsignComboBox->blockSignals(true);
    //startDate->blockSignals(true);
    //endDate->blockSignals(true);
    fillStationCallsignComboBox();
    //qDebug() << Q_FUNC_INFO << ": 1 - " << stationCallsignComboBox->currentText();
    setDefaultStationComboBox();
    //qDebug() << Q_FUNC_INFO << ": 2 - " << stationCallsignComboBox->currentText();
    fillDates();
    //qDebug() << Q_FUNC_INFO << ": 3 - " << stationCallsignComboBox->currentText();
    fillStationMyGridComboBox();
    setDefaultMyGridComboBox();
    //qDebug() << Q_FUNC_INFO << ": 4 - " << stationCallsignComboBox->currentText();
    starting = false;
    updateIfNeeded();
    //qDebug() << Q_FUNC_INFO << ": 5 - " << stationCallsignComboBox->currentText();
    event->accept();
    //qDebug() << Q_FUNC_INFO << " - END";
}

void AdifLoTWExportWidget::setExportMode(const ExportMode _EMode)
{
    //qDebug() << Q_FUNC_INFO << " - Start";
    currentExportMode = _EMode;
    if (currentExportMode == ModeLotW)
    {
        setWindowTitle(tr("KLog - QSOs to be uploaded to LoTW."));
        topLabel->setText(tr("This table shows the QSOs that will be sent to LoTW."));
    }
    else if (currentExportMode == ModeClubLog)
    {
        setWindowTitle(tr("KLog - QSOs to be uploaded to ClubLog."));
        topLabel->setText(tr("This table shows the QSOs that will be sent to ClubLog."));
    }
    else if (currentExportMode == ModeEQSL)
    {
        setWindowTitle(tr("KLog - QSOs to be uploaded to eQSL.cc."));
        topLabel->setText(tr("This table shows the QSOs that will be sent to eQSL.cc."));
    }
    else if (currentExportMode == ModeQRZ)
    {
        setWindowTitle(tr("KLog - QSOs to be uploaded to QRZ.com."));
        topLabel->setText(tr("This table shows the QSOs that will be sent to QRZ.com."));
    }
    else
    {
        setWindowTitle("KLog - QSOs to be exported to ADIF.");
        topLabel->setText(tr("This table shows the QSOs that will be exported to ADIF."));
    }
    //fillStationCallsignComboBox();
    //slotStationCallsignChanged();
    //qDebug() << Q_FUNC_INFO << " - END";
}

void AdifLoTWExportWidget::setLogNumber(const int _logN)
{
    //qDebug() << Q_FUNC_INFO << " - Start";
    if (dataProxy->doesThisLogExist (_logN))
    {
        logNumber = _logN;
    }
    else
    {
        logNumber = -1;
    }
    //qDebug() << Q_FUNC_INFO << " - END";
}

void AdifLoTWExportWidget::setCallValidation(const bool _v)
{
    util->setCallValidation(_v);
    dataProxy->setCallValidation(_v);
}
