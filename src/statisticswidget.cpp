/***************************************************************************
                          statisticswidget.cpp  -  description
                             -------------------
    begin                : oct 2020
    copyright            : (C) 2020 by Jaime Robles
    user                : jaime@robles.es
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

#include "statisticswidget.h"

StatisticsWidget::StatisticsWidget(DataProxy_SQLite *dp, QWidget *parent): QWidget(parent)
{
    //qDebug() << Q_FUNC_INFO << "Start";
    dataProxy = dp;
    statisticToShowComboBox = new QComboBox();
    logComboBox = new QComboBox();
    barChartStats = new BarChartStats(dp, this);
    //donutChartStats = new DonutChartStats(dp, this);

    //chartView = new QChartView(this);
    //graphWidget = new QWidget(this);

    statisticsToShowList.clear();

    createUI();
    connect(statisticToShowComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotChartComboBoxChanged() ) ) ;
    connect(logComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotLogComboBoxChanged() ) ) ;
    //qDebug() << Q_FUNC_INFO << "END";
}


StatisticsWidget::~StatisticsWidget()
{
    //qDebug() << Q_FUNC_INFO << "Start-END";
}

void StatisticsWidget::clear()
{
    //qDebug() << Q_FUNC_INFO << "Start-END";
     //qDebug() <<  "StatisticsWidget::clear()";
}

void StatisticsWidget::closeEvent(QCloseEvent *event)
{
       //qDebug() << "StatisticsWidget::closeEvent";
    //barChartStats->clear();
    //qDebug() << Q_FUNC_INFO << "Start-END";
    event->accept();
    //qDebug() << Q_FUNC_INFO << "END";
}

void StatisticsWidget::showEvent(QShowEvent *event)
{
      //qDebug() << "StatisticsWidget::showEvent";
    //qDebug() << Q_FUNC_INFO << "Start";
    fillLogCombo();
    event->accept();
    //qDebug() << Q_FUNC_INFO << "END";
}

void StatisticsWidget::slotChartComboBoxChanged()
{
       //qDebug() << "StatisticsWidget::slotChartComboBoxChanged: " << statisticToShowComboBox->currentText() ;
    //qDebug() << Q_FUNC_INFO << "Start";
    updateChart();
    statisticToShowComboBox->setFocus();
    //qDebug() << Q_FUNC_INFO << "END";
}

void StatisticsWidget::slotLogComboBoxChanged()
{
    //qDebug() << Q_FUNC_INFO << "Start";
    updateChart();
    logComboBox->setFocus();
    //qDebug() << Q_FUNC_INFO << "END";
}

void StatisticsWidget::updateChart()
{
    //qDebug() << Q_FUNC_INFO << "Start";
    QString text = statisticToShowComboBox->currentText();
    text.truncate(2);
    //qDebug() << Q_FUNC_INFO << " - 010";
    int log = ((logComboBox->currentText()).section('-', 0, 0)).toInt();
    //qDebug() << Q_FUNC_INFO << " - 011";
    //qDebug() << Q_FUNC_INFO << " Text : " << logComboBox->currentText();
    //qDebug() << Q_FUNC_INFO << " Log : " << QString::number(log);
    barChartStats->prepareChart(text.toInt(), log);
    //qDebug() << Q_FUNC_INFO << "END";
}

void StatisticsWidget::createUI()
 {
    //qDebug() << Q_FUNC_INFO << "Start";
     statisticsToShowList << "01-" + tr("QSO per year");
     statisticsToShowList << "02-" + tr("DXCC per year");
     statisticsToShowList << "03-" + tr("CQ zones per year");
     statisticsToShowList << "04-" + tr("QSO per band");
     statisticsToShowList << "05-" + tr("QSO per mode");
     statisticsToShowList << "06-" + tr("QSO per DXCC");
     statisticsToShowList << "07-" + tr("QSO per Continent");
     statisticsToShowList << "08-" + tr("QSO per hour");
     statisticsToShowList << "09-" + tr("QSO per month");
     statisticsToShowList << "10-" + tr("Worked / Confirmed status");
     statisticsToShowList << "11-" + tr("Worked / Sent status");
     statisticsToShowList << "12-" + tr("Sent / Confirmed status");
     statisticsToShowList << "13-" + tr("Satellite grid status");
     statisticsToShowList << "14-" + tr("Satellite DXCC status");
     statisticsToShowList << "15-" + tr("Grids per band status");
     statisticsToShowList << "16-" + tr("DXCC per band status");

     statisticToShowComboBox->addItems(statisticsToShowList);

    fillLogCombo();

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(statisticToShowComboBox);
    hLayout->addWidget(logComboBox);

     QVBoxLayout *layout = new QVBoxLayout;
     layout->addLayout(hLayout);
     layout->addWidget(barChartStats);
     setLayout(layout);
     resize(420,300);
     //qDebug() << Q_FUNC_INFO << "END";
 }

void StatisticsWidget::fillLogCombo()
{
    //qDebug() << Q_FUNC_INFO << "Start";
    QStringList ids;
    ids.clear();
    ids << dataProxy->getListOfManagedLogs();
    QStringList logs;
    logs.clear();

    for (int i = 0; i < ids.size(); ++i)
    {
        //cout << fonts.at(i).toLocal8Bit().constData();
        logs<< ids.at(i) + "-" + dataProxy->getLogDateFromLog((ids.at(i)).toInt()) + "-" + dataProxy->getStationCallSignFromLog((ids.at(i)).toInt());
    }
    logComboBox->clear();
    logComboBox->addItems(logs);
    //qDebug() << Q_FUNC_INFO << "END";
}
