/***************************************************************************
                          qso.cpp  -  description
                             -------------------
    begin                : may 2020
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
#include "qso.h"

QSO::QSO()
{
    logLevel = None;
    qsoId = -1;
}

QSO::~QSO() {}

void QSO::setLogLevel (const DebugLogLevel _b)
{
    logEvent (Q_FUNC_INFO, "Start", Debug);
    logLevel = _b;
    logEvent (Q_FUNC_INFO, "END", Debug);
}

void QSO::logEvent(const QString &_func, const QString &_msg,  DebugLogLevel _level)
{
    if (logLevel<=_level)
        emit debugLog (_func, _msg, _level);
}

void QSO::clear()
{
    logEvent (Q_FUNC_INFO, "Start", Debug);
    qsoId = -1;
    logId = -1;
    backup = false;
    stationCallsign = QString();
    lotwUpdating = false;
    realTime = false;
    manualMode = false;
    keepComment = false;
    keepMyData = false;
    keepOther = false;
    keepSat = false;
    modifying = false;

    // VARIABLES for ADIF //////////
    address = QString();
    age = -1.0;
    a_index = -1;
    ant_az = 0;
    ant_el = 0;
    ant_path = QString();
    arrl_sect = QString();
    award_submitted = QString();
    award_granted = QString();
    band = QString();
    band_rx = QString();
    callsign = QString();
    check = QString();
    clase = QString();
    clublogQSOUpdateDate = QDate();
    clublogDate = QDate();
    clublog_status = QString();
    county = QString();
    comment = QString();
    continent = QString();
    contacted_op = QString();
    contest_id = QString();
    country = QString();
    cqz = -1;
    credit_granted = QString();
    credit_submitted = QString();
    darc_dok = QString();
    distance = 0.0;
    dxcc = -1;
    email = QString();
    ownerCall = QString();
    eQSLRDate = QDate();
    eQSLSDate = QDate();
    eqsl_qsl_rcvd = QString();
    eqsl_qsl_sent = QString();
    fists = -1;
    fists_cc = -1;
    forceInit = false;
    freq = -1.0;
    freq_rx = -1.0;
    freq_tx = -1.0;
    gridsquare = QString();
    operatorCall = QString();
    hrdlogUploadDate = QDate();
    hrdlog_status = QString();
    iota = QString();
    iota_ID = -1;
    itu_zone = -1;
    k_index = -1;
    latitude = QString();
    longitude = QString();
    QSLLoTWRDate = QDate();
    QSLLoTWSDate = QDate();
    lotw_qsl_rcvd = QString();
    lotw_qsl_sent = QString();
    max_bursts = -1;
    mode = QString();
    ms_shower = QString();
    my_antenna = QString();
    my_arrl_sect = QString();
    my_city = QString();
    my_county = QString();
    my_country = QString();
    my_cqz = -1;
    my_dxcc = -1;
    my_fists = QString();
    my_gridsquare = QString();
    my_iota = QString();
    my_iota_ID = -1;
    my_itu_zone = -1;
    my_latitude = QString();
    my_longitude = QString();
    my_name = QString();
    my_postal_code = QString();
    my_rig = QString();
    my_sig = QString();
    my_sig_info = QString();
    my_sota_ref = QString();
    my_state = QString();
    my_street = QString();
    my_usaca_counties = QString();
    my_vucc_grids= QString();
    my_wwff_ref = QString();
    name = QString();
    notes = QString();
    nr_bursts = -1;
    nr_pings = -1;
    operatorCall = QString();
    ownerCall = QString();
    prefix = QString();
    precedence = QString();
    propMode = QString();
    public_key = QString();
    QRZComDate = QDate();
    QRZCom_status = QString();
    qslmsg = QString();
    QSLRDate = QDate();
    QSLSDate = QDate();
    qsl_rcvd = QString();
    qsl_sent = QString();
    qslSenVia = QString();
    qslRecVia = QString();
    qslVia = QString();
    qso_complete = QString();
    qso_dateTime = QDateTime();
    qso_date_off = QDate();
    qso_random = false;
    qth = QString();
    region = QString();
    rig = QString();
    RST_rx = QString();
    RST_tx = QString();
    pwr_rx = 0.0;
    satMode = QString();
    satName = QString();
    sfi = -1;
    sig = QString();
    sig_info = QString();
    silent_key = false;
    skcc = QString();
    sota_ref = QString();
    srx = -1;
    srx_string = QString();
    state = QString();
    stx = -1;
    stx_string = QString();
    submode = QString();
    swl = false;
    ten_ten = -1;
    qso_time_off = QTime();
    pwr_tx = 0.0;
    uksmg = -1;
    usaca_counties = QString();
    ve_prov = QString();
    vucc_grids = QString();
    web = QString();
    wwff_ref = QString();
    logEvent (Q_FUNC_INFO, "END", Debug);
}

void QSO::setBackup(const bool _rt)
{
    backup    = _rt;
}

bool QSO::getBackup()
{
    return backup;
}

void QSO::setModifying(const bool _mod)
{
    modifying = _mod;
}

bool QSO::getModifying()
{
    return modifying;
}

bool QSO::setQSOid(const int _i)
{
    if (_i >0)
    {
        qsoId = _i;
        return true;
    }
    else
    {
        return false;
    }
}

int QSO::getQSOid()
{
    return qsoId;
}

bool QSO::setLogId(const int _i)
{
    if (_i >0)
    {
        logId = _i;
        return true;
    }
    else
    {
        return false;
    }
}

int QSO::getLogId()
{
    return logId;
}

double QSO::setFreqTX(const double _f)
{
    if (_f>0)
    {
        freq_tx = _f;
        return true;
    }
    else {
        return false;
    }
}

bool QSO::setFreqRX(const double _f)
{
    if (_f>0)
    {
        freq_rx = _f;
        return true;
    }
    else {
        return false;
    }
}

double QSO::getFreqTX()
{
    return freq_tx;
}

double QSO::getFreqRX()
{
    return freq_rx;
}

bool QSO::isValid()
{// Add more controls: Call, Date, Time, Band, Mode?
    logEvent (Q_FUNC_INFO, "Start", Debug);
    if ( (callsign.length()>0))
    {
       logEvent (Q_FUNC_INFO, "END-true", Debug);
        return true;
    }
    else
    {
       logEvent (Q_FUNC_INFO, "END-false", Debug);
        return false;
    }
}

bool QSO::setCall(const QString &_c)
{
    logEvent (Q_FUNC_INFO, QString("Start: %1").arg(_c), Debug);
    QString aux;
    aux = _c;
    if (aux.isNull())
    {
        logEvent(Q_FUNC_INFO, "END - False-1", Debug);
        return false;
    }
    if (util->isValidCall(aux))
    {
        logEvent (Q_FUNC_INFO, QString("END - true"), Debug);
        callsign = aux;
        return true;
    }
    else
    {
        logEvent (Q_FUNC_INFO, QString("END - false-2"), Debug);
        return false;
    }
}

QString QSO::getCall()
{
    return callsign;
}

bool QSO::setBand(const QString &_c)
{
   //qDebug() << "QSO::setBand: "<< _c << QT_ENDL;
    if (_c.length()>0)
    {
        band = _c;
        return true;
    }
    else
    {
        band = QString();
        return false;
    }
}

QString QSO::getBand()
{
    return band;
}

bool QSO::setBandRX(const QString &_c)
{
   //qDebug() << "QSO::setBandRX: "<< _c << QT_ENDL;
    if (_c.length()>0)
    {
        band_rx = _c;
        return true;
    }
    else
    {
        band_rx = QString();
        return false;
    }
}

QString QSO::getBandRX()
{
    return band;
}

bool QSO::setMode(const QString &_c)
{
    logEvent (Q_FUNC_INFO, "Start", Debug);
    QString aux = _c;
    if (aux.isNull())
    {
        mode = QString();
        logEvent (Q_FUNC_INFO, "END - False 1", Debug);
        return false;
    }
    if (aux.length()>0)
    {
        mode = aux;
        logEvent (Q_FUNC_INFO, "END - True", Debug);
        return true;
    }
    else
    {
        mode = QString();
        logEvent (Q_FUNC_INFO, "END - False 2", Debug);
        return false;
    }
}

QString QSO::getMode()
{
    return mode;
}

bool QSO::setDate(const QDate &_c)
{
    if (_c.isValid())
    {
        qso_dateTime.setDate(_c);
        return true;
    }
    else
    {
        return false;
    }
}

QDate QSO::getDate()
{
    return qso_dateTime.date();
}

bool QSO::setDateOff(const QDate &_c)
{
    if (_c.isValid())
    {
        qso_date_off = _c;
        return true;
    }
    else
    {
        qso_date_off = QDate();
        return false;
    }
}

QDate QSO::getDateOff()
{
    return qso_date_off;
}

bool QSO::setTimeOff(const QTime &_c)
{
    if (_c.isValid())
    {
        qso_time_off = _c;
        return true;
    }
    else
    {
        qso_time_off = QTime();
        return false;
    }
}

QTime QSO::getTimeOff()
{
    return qso_time_off;
}

bool QSO::setTimeOn(const QTime &_c)
{
   //qDebug() << "QSO::setQSLTime: " << _c.toString("mmhhss") << QT_ENDL;
    if (_c.isValid())
    {
       //qDebug() << "QSO::setQSLTime: VALID" << QT_ENDL;
        qso_dateTime.setTime(_c);
        return true;
    }
    else
    {
        return false;
    }
}

QTime QSO::getTimeOn()
{
    return qso_dateTime.time();
}

bool QSO::setDateTimeOn(const QDateTime &_c)
{
    if (_c.isValid())
    {
        qso_dateTime = _c;
        return true;
    }
    else
    {
        return false;
    }
}

QDateTime QSO::getDateTimeOn()
{
    return qso_dateTime;
}

void QSO::setRealTime(const bool _rt)
{
    realTime = _rt;
}

bool QSO::getRealTime()
{
    return realTime;
}

void QSO::setManualMode(const bool _rt)
{
    manualMode = _rt;
}

bool QSO::getManualMode()
{
    return manualMode;
}

// eQSL Tab

bool QSO::setClubLogStatus(const QString &_c)
{
    if (util->isValidUpload_Status (_c))
    {
        clublog_status = _c;
        return true;
    }
    else
    {
        return false;
    }
}

QString QSO::getClubLogStatus()
{
    return clublog_status;
}

bool QSO::setClubLogDate(const QDate &_c)
{
    if (_c.isValid())
    {
        clublogDate = _c;
        return true;
    }
    else
    {
        clublogDate = QDate();
        return false;
    }
}

QDate QSO::getClubLogDate()
{
    return clublogDate;
}

bool QSO::setQRZCOMStatus(const QString &_c)
{
    {
        if (util->isValidUpload_Status (_c))
        {
            QRZCom_status = _c;
            return true;
        }
        else
        {
            return false;
        }
    }
}

QString QSO::getQRZCOMStatus()
{
    return QRZCom_status;
}

bool QSO::setQRZCOMDate(const QDate &_c)
{
    if (_c.isValid())
    {
        clublogDate = _c;
        return true;
    }
    else
    {
        clublogDate = QDate();
        return false;
    }
}

QDate QSO::getQRZCOMDate()
{
    return QRZComDate;
}

bool QSO::setEQSLQSL_RCVD(const QString &_c)
{
    if (util->isValidQSL_Rcvd(_c))
    {
        eqsl_qsl_rcvd = _c;
        return true;
    }
    else
    {
        return false;
    }
}

QString QSO::getEQSLQSL_RCVD()
{
    return eqsl_qsl_rcvd;
}

bool QSO::setEQSLQSL_SENT(const QString &_c)
{
    if (util->isValidQSL_Sent(_c))
    {
        eqsl_qsl_sent = _c;
        return true;
    }
    else {
        return false;
    }
}

QString QSO::getEQSLQSL_SENT()
{
    return eqsl_qsl_sent;
}

bool QSO::setEQSLQSLRDate(const QDate &_c)
{
    if (_c.isValid())
    {
        eQSLRDate = _c;
        return true;
    }
    else
    {
        eQSLRDate = QDate();
        return false;
    }
}

QDate QSO::getEQSLQSLRDate()
{
    return eQSLRDate;
}

bool QSO::setEQSLQSLSDate(const QDate &_c)
{
    if (_c.isValid())
    {
        eQSLSDate = _c;
        return true;
    }
    else
    {
        eQSLSDate = QDate();
        return false;
    }
}

QDate QSO::getEQSLQSLSDate()
{
    return eQSLSDate;
}

bool QSO::setLoTWQSL_SENT(const QString &_c)
{
    if (util->isValidQSL_Sent(_c))
    {
        lotw_qsl_sent = _c;
        return true;
    }
    else
    {
        return false;
    }
}

QString QSO::getLoTWQSL_SENT()
{
    return lotw_qsl_sent;
}

bool QSO::setLoTWQSLSDate(const QDate &_c)
{
    //qDebug() << Q_FUNC_INFO;
    if (_c.isValid())
    {
        //qDebug() << Q_FUNC_INFO << " - valid";
        QSLLoTWSDate = _c;
        return true;
    }
    else
    {
        //qDebug() << Q_FUNC_INFO << " - NOT valid";
        QSLLoTWSDate = QDate();
        return false;
    }
}

QDate QSO::getLoTWQSLSDate()
{
    return QSLLoTWSDate;
}

bool QSO::setLoTWQSL_RCVD(const QString &_c)
{
    //qDebug() << "QSO::setLoTWQSL_RCVD: " << _c  << QT_ENDL;
    if (util->isValidQSL_Rcvd(_c))
    {
        //qDebug() << "QSO::setLoTWQSL_RCVD: VALID " << QT_ENDL;
        lotw_qsl_rcvd = _c;
        return true;
    }
    else
    {
        //qDebug() << "QSO::setLoTWQSL_RCVD: NOT valid " << QT_ENDL;
        return false;
    }
}

QString QSO::getLoTWQSL_RCVD()
{
    return lotw_qsl_rcvd;
}

bool QSO::setLoTWQSLRDate(const QDate &_c)
{
    //qDebug() << "QSO::setLoTWQSLRDate: " << _c.toString("yyyy-MM-dd") << QT_ENDL;
    if (_c.isValid())
    {
        //qDebug() << "QSO::setLoTWQSLRDate: TRUE" << QT_ENDL;
        QSLLoTWRDate = _c;
        return true;
    }
    else
    {
        //qDebug() << "QSO::setLoTWQSLRDate: FALSE" << QT_ENDL;
        QSLLoTWRDate = QDate();
        return false;
    }
}

QDate QSO::getLoTWQSLRDate()
{
    return QSLLoTWRDate;
}

// QSL TAB
bool QSO::setQSL_SENT(const QString &_c)
{
    if (util->isValidQSL_Sent (_c))
    {
        qsl_sent = _c;
        return true;
    }
    else
    {
        return false;
    }
}

QString QSO::getQSL_SENT()
{
    return qsl_sent;
}

bool QSO::setQSLSDate(const QDate &_c)
{
    if (_c.isValid())
    {
        QSLSDate = _c;
        return true;
    }
    else
    {
        QSLSDate = QDate();
        return false;
    }
}

QDate QSO::getQSLSDate()
{
    return QSLSDate;
}

bool QSO::setQSL_RCVD(const QString &_c)
{
    if (util->isValidQSL_Rcvd(_c))
    {
        qsl_rcvd = _c;
        return true;
    }
    else {
        return false;
    }
}

QString QSO::getQSL_RCVD()
{
    return qsl_rcvd;
}

bool QSO::setQSLSenVia(const QString &_qs)
{
    if (!_qs.isEmpty ())
    {
        qslSenVia = _qs;
        return true;
    }
    else
    {
        return false;
    }
}

QString QSO::getSentVia()
{
    return qslSenVia;
}

bool QSO::setQSLRecVia(const QString &_qs)
{
    if (!_qs.isEmpty ())
    {
        qslRecVia = _qs;
        return true;
    }
    else
    {
        return false;
    }
}

QString QSO::getRecVia()
{
    return qslRecVia;
}

bool QSO::setQSLVia(const QString &_qs)
{
    if (!_qs.isEmpty ())
    {
        qslVia = _qs;
        return true;
    }
    else
    {
        return false;
    }
}

QString QSO::getQSLVia()
{
    return qslVia;
}

bool QSO::setQSLRDate(const QDate &_c)
{
    if (_c.isValid())
    {
        QSLRDate = _c;
        return true;
    }
    else
    {
        QSLRDate = QDate();
        return false;
    }
}

QDate QSO::getQSLRDate()
{
    return QSLRDate;
}

bool QSO::setQSLMsg(const QString &_qs)
{
    if (!_qs.isEmpty ())
    {
        qslmsg = _qs;
        return true;
    }
    else
    {
        return false;
    }
}

QString QSO::getQSLMsg()
{
    return qslmsg;
}

void QSO::setLoTWUpdating(bool _lotw)
{
    lotwUpdating = _lotw;
}

void QSO::setDefaultEQSLSentServices(const bool _send)
{
    if (_send)
    {
        if ((getLoTWQSL_SENT()).isEmpty())
        {
            setLoTWQSL_SENT ("Q");
        }
        if ((getClubLogStatus ()).isEmpty())
        {
            setClubLogStatus ("M");
        }
        if ((getEQSLQSL_SENT ()).isEmpty())
        {
            setEQSLQSL_SENT ("Q");
        }
        if ((getQRZCOMStatus ()).isEmpty())
        {
            setQRZCOMStatus ("M");
        }
    }
}

bool QSO::setGridSquare(const QString &_c)
{
    //qDebug() << Q_FUNC_INFO << ": " << _c;
    if (util->isValidGrid(_c))
    {
        gridsquare = _c;
        return true;
    }
    else
    {
        return false;
    }
}

QString QSO::getGridSquare()
{
    //qDebug() << Q_FUNC_INFO << ": " << gridsquare;
    return gridsquare;
}

bool QSO::setQTH(const QString &_c)
{
    if (!_c.isEmpty ())
    {
        qth = _c;
        return true;
    }
    else
    {
        return false;
    }
}

QString QSO::getQTH()
{
    return qth;
}

bool QSO::setName(const QString &_c)
{
    if (!_c.isEmpty ())
    {
        name = _c;
        return true;
    }
    else
    {
        return false;
    }
}

QString QSO::getName()
{
    return name;
}

bool QSO::setRSTRX(const QString &_c)
{
    if (!_c.isEmpty ())
    {
        RST_rx = _c;
        return true;
    }
    else
    {
        return false;
    }
}

QString QSO::getRSTRX()
{
    return RST_rx;
}

bool QSO::setRSTTX(const QString &_c)
{
    if (!_c.isEmpty ())
    {
        RST_tx = _c;
        return true;
    }
    else
    {
        return false;
    }
}

QString QSO::getRSTTX()
{
    return RST_tx;
}

bool QSO::setRXPwr(const double _f)
{
    if (_f>0)
    {
        pwr_rx = _f;
        return true;
    }
    else {
        return false;
    }
}

double QSO::getRXPwr()
{
    return pwr_rx;
}

// Comment Tab
bool QSO::setComment(const QString &_c)
{
    if (!_c.isNull ())
    {
        comment = _c;
        return true;
    }
    else
    {
        return false;
    }
}

QString QSO::getComment()
{
    return comment;
}

bool QSO::setKeepComment(bool _k)
{
    keepComment = _k;
    return true;
}

bool QSO::getKeepComment()
{
    return keepComment;
}

// Other Tab
bool QSO::setDXCC(const int _i)
{
    if (util->isValidDXCC(_i))
    {
        dxcc = _i;
        return true;
    }
    return false;
}

int QSO::getDXCC()
{
    return dxcc;
}

bool QSO::setPropMode(const QString &_c)
{
    //qDebug() << Q_FUNC_INFO << _c;
    QString aux;
    aux = _c;
    if (aux.isNull())
    {
        logEvent(Q_FUNC_INFO, "END - False-1", Debug);
        return false;
    }
    if (aux.length()>0)
    {
        propMode = _c;
        return true;
    }
    else
    {
        propMode = QString();
        return false;
    }
}

QString QSO::getPropMode()
{
    return propMode;
}


bool QSO::setSOTA_REF(const QString &_c)
{
    if (_c.length ()>1)
    {
        sota_ref = _c;
        return true;
    }
    return false;
}

QString QSO::getSOTA_REF()
{
    return sota_ref;
}

bool QSO::setMySOTA_REF(const QString &_c)
{
    if (_c.length ()>1)
    {
        my_sota_ref = _c;
        return true;
    }
    return false;
}

QString QSO::getMySOTA_REF()
{
    return my_sota_ref;
}

bool QSO::setMyRig(const QString &_c)
{
    if (_c.length ()>1)
    {
        my_rig = _c;
        return true;
    }
    return false;
}

bool QSO::setVUCCGrids(const QString &_c)
{
    if (util->isValidVUCCGrids (_c))
    {
        vucc_grids = _c;
        return true;
    }
    else
    {
        return false;
    }
}

QString QSO::getVUCCGrids()
{
    return vucc_grids;
}

bool QSO::setMyVUCCGrids(const QString &_c)
{
    if (util->isValidVUCCGrids (_c))
    {
        my_vucc_grids = _c;
        return true;
    }
    else
    {
        return false;
    }
}

QString QSO::getMyVUCCGrids()
{
    return my_vucc_grids;
}

QString QSO::getMyRig()
{
    return my_rig;
}

bool QSO::setMyAntenna(const QString &_c)
{
    if (_c.length ()>1)
    {
        my_antenna = _c;
        return true;
    }
    return false;
}

QString QSO::getMyAntenna()
{
    return my_antenna;
}

bool QSO::setMyArrlSect(const QString &_c)
{
    if (!util->isValidARRLSect (_c))
    {
        return false;
    }
    else
    {
        my_arrl_sect = _c;
        return true;
    }
}

QString QSO::getMyArrlSect()
{
    return my_arrl_sect;
}

bool QSO::setAge(const double _c)
{
    if ((0 <= _c) && (_c <= 120))
    {
        age = _c;
        return true;
    }
    return false;
}

double QSO::getAge()
{
    return age;
}

bool QSO::setIOTA(const QString &_c)
{
    if (_c.length()>0)
    {
        iota = _c;
        return true;
    }
    else
    {
        iota = QString();
        return false;
    }
}

QString QSO::getIOTA()
{
    return iota;
}

bool QSO::setKeepOthers(bool _k)
{
    keepOther = _k;
    return true;
}

bool QSO::getKeepOthers()
{
    return keepOther;
}

// My Data
bool QSO::setTXPwr(double _f)
{
    logEvent (Q_FUNC_INFO, "Start", Debug);
    if (_f>0)
    {
        pwr_tx = _f;
        logEvent (Q_FUNC_INFO, "END - True", Debug);
        return true;
    }
    else {
        logEvent (Q_FUNC_INFO, "END - False", Debug);
        return false;
    }
}

double QSO::getTXPwr()
{
    return pwr_tx;
}

bool QSO::setOperatorCallsign(const QString &_c)
{
    //qDebug() << Q_FUNC_INFO << "Start: " << _c;
    //logEvent(Q_FUNC_INFO, "Start", Debug);
    QString aux = _c;
    if (aux.length()<3)
        return false;


    if (util->isValidCall(aux))
    {
       operatorCall = aux;
       //qDebug() << Q_FUNC_INFO << "END - true";
       logEvent(Q_FUNC_INFO, "END-true", Debug);
       return true;
    }
    else {
        //qDebug() << Q_FUNC_INFO << "End - false";
        logEvent(Q_FUNC_INFO, "END-false", Debug);
        return false;
    }
}

QString QSO::getOperatorCallsign()
{
    return operatorCall;
}

bool QSO::setStationCallsign(const QString &_c)
{
    //qDebug() << Q_FUNC_INFO << "Start: " << _c;
    QString aux = _c;
    if ((aux.length()<3) || (aux.isNull()))
    {
        //qDebug() << Q_FUNC_INFO << " - 009";
        return false;
    }


    //qDebug() << Q_FUNC_INFO << " - 010";
    if (util->isValidCall(aux))
    {
        //qDebug() << Q_FUNC_INFO << " - True";
        stationCallsign = aux;
        return true;
    }
    else
    {
        //qDebug() << Q_FUNC_INFO << " - False";
       return false;
    }
}

QString QSO::getStationCallsign()
{
    return stationCallsign;
}

bool QSO::setMyGridSquare(const QString &_c)
{
    if (util->isValidGrid(_c))
    {
        my_gridsquare = _c;
        return true;
    }
    else
    {
        return false;
    }
}

QString QSO::getMyGridSquare()
{
    return my_gridsquare;
}

bool QSO::setKeepMyData(bool _k)
{
    keepMyData = _k;
    return true;
}

bool QSO::getKeepMyData()
{
    return keepMyData;
}

// Satellite Tab
bool setKeepSatTab(bool _k);

bool getKeepSatTab();

bool QSO::setSatName(const QString &_c)
{
    if (_c.length()>0)
    {
        satName = _c;
        return true;
    }
    else
    {
        satName = QString();
        return false;
    }
}

QString QSO::getSatName()
{
    return satName;
}

bool QSO::setSatMode(const QString &_c)
{
    //qDebug() << Q_FUNC_INFO << ": " << _c;
    if (_c.length()>0)
    {
        satMode = _c;
        return true;
    }
    else
    {
        satMode = QString();
        return false;
    }
}

QString QSO::getSatMode()
{
    return satMode;
}

bool QSO::setKeepSatTab(bool _k)
{
    keepSat = _k;
    return true;
}

bool QSO::getKeepSatTab()
{
    return keepSat;
}

bool QSO::setAddress(const QString &_c)
{
   address = _c;
   return true;
}

QString QSO::getAddress()
{
    return address;
}

bool QSO::setA_Index(const int _i)
{
    if ((_i>=0) && (_i<=400))
    {
        a_index = _i;
        return true;
    }
    return false;
}

int QSO::getA_Index()
{
    return a_index;
}


bool QSO::setAnt_az(const double _c)
{ //TODO: Adjust number: http://www.adif.org/312/ADIF_312.htm#QSO_Field_ANT_AZ
    if ((0 <= _c) && (_c <= 360))
    {
        ant_az = _c;
        return true;
    }
    return false;
}
double QSO::getAnt_az()
{
    return ant_az;
}

bool QSO::setAnt_el(const double _c)
{ //TODO: Adjust number: http://www.adif.org/312/ADIF_312.htm#QSO_Field_ANT_EL
    if ((-90 <= _c) && (_c <= 90))
    {
        ant_el = _c;
        return true;
    }
    return false;
}

double QSO::getAnt_el()
{
    return ant_el;
}

bool QSO::setAnt_Path(const QString &_c)
{
    if (!util->isValidAntPath (_c))
        return false;
    ant_path = _c;
    return true;
}

QString QSO::getAnt_Path()
{
    return ant_path;
}

bool QSO::setARRL_Sect(const QString &_c)
{
    if (!util->isValidARRLSect (_c))
        return false;
    arrl_sect = _c;
    return true;
}

QString QSO::getARRL_Sect()
{
    return arrl_sect;
}

bool QSO::setCheck(const QString &_c)
{
    check = _c;
    return true;
}

QString QSO::getCheck()
{
    return check;
}

bool QSO::setClase(const QString &_c)
{
    clase = _c;
    return true;
}

QString QSO::getClase()
{
    return clase;
}

bool QSO::setClublogQSOUpdateDate(const QDate &_c)
{
    if (_c.isValid())
    {
        clublogQSOUpdateDate = _c;
        return true;
    }
    else
    {
        clublogQSOUpdateDate = QDate();
        return false;
    }
}

QDate QSO::getClublogQSOUpdateDate()
{
    return clublogQSOUpdateDate;
}

bool QSO::setContinent(const QString &_c)
{
    if (!util->isValidContinent (_c))
        return false;
    continent = _c;
    return true;
}

QString QSO::getContinent()
{
    return continent;
}

bool QSO::setDistance(const double _i)
{
    if (util->isValidDistance(_i))
    {
        distance = _i;
        return true;
    }
    return false;
}

double QSO::getDistance()
{
    return distance;
}

bool QSO::setOwnerCallsign(const QString &_c)
{
    if (util->isValidCall(_c))
    {
       ownerCall = _c;
       return true;
    }
    else {
       return false;
    }
}

QString QSO::getOwnerCallsign()
{
    return ownerCall;
}

bool QSO::setHRDUpdateDate(const QDate &_c)
{
    if (_c.isValid())
    {
        hrdlogUploadDate = _c;
        return true;
    }
    else
    {
        hrdlogUploadDate = QDate();
        return false;
    }
}

QDate QSO::getHRDUpdateDate()
{
    return hrdlogUploadDate;
}

bool QSO::setHRDLogStatus(const QString &_c)
{
    if (util->isValidUpload_Status (_c))
    {
        hrdlog_status = _c;
        return true;
    }
    else
    {
        return false;
    }
}

QString QSO::getHRDLogStatus()
{
    return hrdlog_status;
}

bool QSO::setFreq(const double _f)
{
    if (_f>0)
    {
        freq = _f;
        return true;
    }
    else {
        return false;
    }
}

double QSO::getFreq()
{
    return freq;
}

bool QSO::setK_Index(const int _i)
{
    if ((_i>=0) && (_i<=400))
    {
        k_index = _i;
        return true;
    }
    return false;
}

int QSO::getK_Index()
{
    return k_index;
}

bool QSO::setRig(const QString &_c)
{
    rig = _c;
    return true;
}

QString QSO::getRig()
{
    return rig;
}

bool QSO::setCountry(const QString &_c)
{
    country = _c;
    return true;
}

QString QSO::getCountry()
{
    return country;
}

bool QSO::setAwardGranted(const QString &_c)
{
    award_granted = _c;
    return true;
}

QString QSO::getAwardGranted()
{
    return award_granted;
}

bool QSO::setAwardSubmitted(const QString &_c)
{
    award_submitted = _c;
    return true;
}

QString QSO::getAwardSubmitted()
{
    return award_submitted;
}

bool QSO::setCounty(const QString &_c)
{
    county = _c;
    return true;
}

QString QSO::getCounty()
{
    return county;
}

bool QSO::setContactedOperator(const QString &_c)
{
    if (util->isValidCall(_c))
    {
       contacted_op = _c;
       return true;
    }
    else {
       return false;
    }
}

QString QSO::getContactedOperator()
{
    return contacted_op;
}

bool QSO::setContestID(const QString &_c)
{
    contest_id = _c;
    return true;
}

QString QSO::getContestID()
{
    return contest_id;
}

bool QSO::setCQZone(const int _i)
{
    if ((_i>=0) && (_i<=40))
    {
        cqz = _i;
        return true;
    }
    else
    {
        return false;
    }
}

int QSO::getCQZone()
{
    return cqz;
}

bool QSO::setCreditGranted(const QString &_c)
{
    credit_granted = _c;
    return true;
}

QString QSO::getCreditGranted()
{
    return credit_granted;
}

bool QSO::setCreditSubmitted(const QString &_c)
{
    credit_submitted = _c;
    return true;
}

QString QSO::getCreditSubmitted()
{
    return credit_submitted;
}

bool QSO::setDarcDok(const QString &_c)
{
    darc_dok = _c;
    return true;
}

QString QSO::getDarcDok()
{
    return darc_dok;
}

bool QSO::setEmail(const QString &_c)
{
    email = _c;
    return true;
}

QString QSO::getEmail()
{
    return email;
}

bool QSO::setFists(const int _i)
{
    if (_i>=0)
    {
        fists = _i;
        return true;
    }
    else
    {
        return false;
    }
}

int QSO::getFists()
{
    return fists;
}

bool QSO::setFistsCC(const int _i)
{
    if (_i>=0)
    {
        fists_cc = _i;
        return true;
    }
    else
    {
        return false;
    }
}

int QSO::getFistsCC()
{
    return fists_cc;
}

bool QSO::setForceInit(bool _k)
{
    forceInit = _k;
    return true;
}

bool QSO::getForceInit()
{
    return forceInit;
}

bool QSO::setIotaID(const int _i)
{
    if (_i>=0)
    {
        iota_ID = _i;
        return true;
    }
    else
    {
        return false;
    }
}

int QSO::getIotaID()
{
    return iota_ID;
}

bool QSO::setItuZone(const int _i)
{
    if (_i>=0 && (_i<=90))
    {
        itu_zone = _i;
        return true;
    }
    else
    {
        return false;
    }
}

int QSO::getItuZone()
{
    return itu_zone;
}

bool QSO::setLatitude(const QString &_c)
{
    latitude = _c;
    return true;
}

QString QSO::getLatitude()
{
    return latitude;
}

bool QSO::setLongitude(const QString &_c)
{
    longitude = _c;
    return true;
}

QString QSO::getLongitude()
{
    return longitude;
}

bool QSO::setNrBursts(const int _i)
{
    if (_i>=0)
    {
        nr_bursts = _i;
        return true;
    }
    else
    {
        return false;
    }
}

int QSO::getNrBursts()
{
    return nr_bursts;
}

bool QSO::setMaxBursts(const int _i)
{
    if (_i>=0)
    {
        max_bursts = _i;
        return true;
    }
    else
    {
        return false;
    }
}

int QSO::getMaxBursts()
{
    return max_bursts;
}

bool QSO::setNrPings(const int _i)
{
    if (_i>=0)
    {
        nr_pings = _i;
        return true;
    }
    else
    {
        return false;
    }
}

int QSO::getNrPings()
{
    return nr_pings;
}

bool QSO::setMsShower(const QString &_c)
{
    ms_shower = _c;
    return true;
}

QString QSO::getMsShower()
{
    return ms_shower;
}

bool QSO::setQSOComplete(const QString &_c)
{
    qso_complete = _c;
    return true;
}

QString QSO::getQSOComplete()
{
    return qso_complete;
}

bool QSO::setQSORandom(bool _k)
{
    qso_random = _k;
    return true;
}

bool QSO::getQSORandom()
{
    return qso_random;
}

bool QSO::setMyCity(const QString &_c)
{
    my_city = _c;
    return true;
}

QString QSO::getMyCity()
{
    return my_city;
}

bool QSO::setMyCounty(const QString &_c)
{
    my_county = _c;
    return true;
}

QString QSO::getMyCounty()
{
    return my_county;
}

bool QSO::setMyCountry(const QString &_c)
{
    my_country = _c;
    return true;
}

QString QSO::getMyCountry()
{
    return my_country;
}

bool QSO::setMyCQZone(const int _i)
{
    if ((_i>=0) && (_i<=40))
    {
        my_cqz = _i;
        return true;
    }
    else
    {
        return false;
    }
}

int QSO::getMyCQZone()
{
    return my_cqz;
}

bool QSO::setMyDXCC(const int _i)
{
    if (util->isValidDXCC(_i))
    {
        my_dxcc = _i;
        return true;
    }
    return false;
}

int QSO::getMyDXCC()
{
    return my_dxcc;
}

bool QSO::setMyFists(const QString &_c)
{
    my_fists = _c;
    return true;
}

QString QSO::getMyFists()
{
    return my_fists;
}

bool QSO::setMyIOTA(const QString &_c)
{
    if (_c.length()>0)
    {
        my_iota = _c;
        return true;
    }
    else
    {
        my_iota = QString();
        return false;
    }
}

QString QSO::getMyIOTA()
{
    return iota;
}

bool QSO::setMyIotaID(const int _i)
{
    if (_i>=0)
    {
        my_iota_ID = _i;
        return true;
    }
    else
    {
        return false;
    }
}

int QSO::getMyIotaID()
{
    return my_iota_ID;
}

bool QSO::setMyITUZone(const int _i)
{
    if (_i>=0 && (_i<=90))
    {
        my_itu_zone = _i;
        return true;
    }
    else
    {
        return false;
    }
}

int QSO::getMyITUZone()
{
    return my_itu_zone;
}

bool QSO::setMyLatitude(const QString &_c)
{
    my_latitude = _c;
    return true;
}

QString QSO::getMyLatitude()
{
    return my_latitude;
}

bool QSO::setMyLongitude(const QString &_c)
{
    my_longitude = _c;
    return true;
}

QString QSO::getMyLongitude()
{
    return my_longitude;
}

bool QSO::setMyName(const QString &_c)
{
    my_name = _c;
    return true;
}

QString QSO::getMyName()
{
    return my_name;
}

bool QSO::setMyPostalCode(const QString &_c)
{
    my_postal_code = _c;
    return true;
}

QString QSO::getMyPostalCode()
{
    return my_postal_code;
}

bool QSO::setMySig(const QString &_c)
{
    my_sig = _c;
    return true;
}

QString QSO::getMySig()
{
    return my_sig;
}

bool QSO::setMySigInfo(const QString &_c)
{
    my_sig_info = _c;
    return true;
}

QString QSO::getMySigInfo()
{
    return my_sig_info;
}

bool QSO::setMyState(const QString &_c)
{
    my_state = _c;
    return true;
}

QString QSO::getMyState()
{
    return my_state;
}

bool QSO::setMyStreet(const QString &_c)
{
    my_street = _c;
    return true;
}

QString QSO::getMyStreet()
{
    return my_street;
}

bool QSO::setMyUsacaCounties(const QString &_c)
{
    my_usaca_counties = _c;
    return true;
}

QString QSO::getMyUsacaCounties()
{
    return my_usaca_counties;
}

bool QSO::setNotes(const QString &_c)
{
    notes = _c;
    return true;
}

QString QSO::getNotes()
{
    return notes;
}

bool QSO::setPrefix(const QString &_c)
{
    prefix = _c;
    return true;
}

QString QSO::getPrefix()
{
    return prefix;
}

bool QSO::setPrecedence(const QString &_c)
{
    precedence = _c;
    return true;
}

QString QSO::getPrecedence()
{
    return precedence;
}

bool QSO::setPublicKey(const QString &_c)
{
    public_key = _c;
    return true;
}

QString QSO::getPublicKey()
{
    return public_key;
}

bool QSO::setQslMsg(const QString &_c)
{
    qslmsg = _c;
    return true;
}

QString QSO::getQslMsg()
{
    return qslmsg;
}

bool QSO::setRegion(const QString &_c)
{
    region = _c;
    return true;
}

QString QSO::getRegion()
{
    return region;
}

bool QSO::setTenTen(const int _i)
{
    if (_i>=0)
    {
        ten_ten = _i;
        return true;
    }
    else
    {
        return false;
    }
}

int QSO::getTenTen()
{
    return ten_ten;
}

bool QSO::setSFI(const int _i)
{
    if (_i>=0 && (_i<=300))
    {
        sfi = _i;
        return true;
    }
    else
    {
        return false;
    }
}

int QSO::getSFI()
{
    return sfi;
}

bool QSO::setSig(const QString &_c)
{
    sig = _c;
    return true;
}

QString QSO::getSig()
{
    return sig;
}

bool QSO::setSigInfo(const QString &_c)
{
    sig_info = _c;
    return true;
}

QString QSO::getSigInfo()
{
    return sig_info;
}

bool QSO::setSilentKey(bool _k)
{
    silent_key = _k;
    return true;
}

bool QSO::getSilentKey()
{
    return silent_key;
}

bool QSO::setSkcc(const QString &_c)
{
    skcc = _c;
    return true;
}

QString QSO::getSkcc()
{
    return skcc;
}

bool QSO::setSrx(const int _i)
{
    if (_i>=0)
    {
        srx = _i;
        return true;
    }
    else
    {
        return false;
    }
}

int QSO::getSrx()
{
    return srx;
}

bool QSO::setSrxString(const QString &_c)
{
    srx_string = _c;
    return true;
}

QString QSO::getSrxString()
{
    return srx_string;
}

bool QSO::setStx(const int _i)
{
    if (_i>=0)
    {
        stx = _i;
        return true;
    }
    else
    {
        return false;
    }
}

int QSO::getStx()
{
    return stx;
}

bool QSO::setStxString(const QString &_c)
{
    stx_string = _c;
    return true;
}

QString QSO::getStxString()
{
    return stx_string;
}

bool QSO::setState(const QString &_c)
{
    state = _c;
    return true;
}

QString QSO::getState()
{
    return state;
}

bool QSO::setSubmode(const QString &_c)
{
    submode = _c;
    return true;
}

QString QSO::getSubmode()
{
    return submode;
}

bool QSO::setSwl(bool _k)
{
    swl = _k;
    return true;
}

bool QSO::getSwl()
{
    return swl;
}

bool QSO::setUksmg(const int _i)
{
    if (_i>=0)
    {
        uksmg = _i;
        return true;
    }
    else
    {
        return false;
    }
}

int QSO::getUksmg()
{
    return uksmg;
}

bool QSO::setUsacaCounties(const QString &_c)
{
    usaca_counties = _c;
    return true;
}

QString QSO::getUsacaCounties()
{
    return usaca_counties;
}

bool QSO::setVeProv(const QString &_c)
{
    ve_prov = _c;
    return true;
}

QString QSO::getVeProv()
{
    return ve_prov;
}

bool QSO::setWeb(const QString &_c)
{
    web = _c;
    return true;
}

QString QSO::getWeb()
{
    return web;
}

bool QSO::setWwffRef(const QString &_c)
{
    wwff_ref = _c;
    return true;
}

QString QSO::getWwffRef()
{
    return wwff_ref;
}

bool QSO::setMyWwffRef(const QString &_c)
{
    my_wwff_ref = _c;
    return true;
}

QString QSO::getMyWwffRef()
{
    return my_wwff_ref;
}


// helper functions for hash, returns original function but takes string data as imput
bool QSO::setAge(const QString &data) { return setAge(data.toInt()); }
bool QSO::setA_Index(const QString& data) { return setA_Index(data.toInt()); }
bool QSO::setAnt_az(const QString& data) { return setAnt_az(data.toInt()); }
bool QSO::setAnt_el(const QString& data) { return setAnt_el(data.toInt()); }
bool QSO::setCQZone(const QString& data) { return setCQZone(data.toInt()); }
bool QSO::setDistance(const QString& data) { return setDistance(data.toInt()); }
bool QSO::setDXCC(const QString& data) { return setDXCC(data.toInt()); }
bool QSO::setFists(const QString& data) { return setFists(data.toInt()); }
bool QSO::setFistsCC(const QString& data) { return setFistsCC(data.toInt()); }
bool QSO::setIotaID(const QString& data) { return setIotaID(data.toInt()); }
bool QSO::setItuZone(const QString& data) { return setItuZone(data.toInt()); }
bool QSO::setK_Index(const QString& data) { return setK_Index(data.toInt()); }
bool QSO::setMaxBursts(const QString& data) { return setMaxBursts(data.toInt()); }
bool QSO::setMyCQZone(const QString& data) { return setMyCQZone(data.toInt()); }
bool QSO::setMyDXCC(const QString& data) { return setMyDXCC(data.toInt()); }
bool QSO::setMyIotaID(const QString& data) { return setMyIotaID(data.toInt()); }
bool QSO::setMyITUZone(const QString& data) { return setMyITUZone(data.toInt()); }
bool QSO::setNrBursts(const QString& data) { return setNrBursts(data.toInt()); }
bool QSO::setNrPings(const QString& data) { return setNrPings(data.toInt()); }
bool QSO::setSFI(const QString& data) { return setSFI(data.toInt()); }
bool QSO::setSrx(const QString& data) { return setSrx(data.toInt()); }
bool QSO::setStx(const QString& data) { return setStx(data.toInt()); }
bool QSO::setTenTen(const QString& data) { return setTenTen(data.toInt()); }
bool QSO::setUksmg(const QString& data) { return setUksmg(data.toInt()); }

bool QSO::setFreqTX(const QString& data) { return setFreqTX(data.toDouble()); }
bool QSO::setFreqRX(const QString& data) { return setFreqRX(data.toDouble()); }
bool QSO::setRXPwr(const QString& data){ return setRXPwr(data.toDouble()); }
bool QSO::setTXPwr(const QString& data){ return setTXPwr(data.toDouble()); }

bool QSO::setClublogQSOUpdateDate(const QString& data) { return setClublogQSOUpdateDate(util->getDateFromADIFDateString(data)); }
bool QSO::setEQSLQSLRDate(const QString& data) { return setEQSLQSLRDate(util->getDateFromADIFDateString(data)); }
bool QSO::setEQSLQSLSDate(const QString& data) { return setEQSLQSLSDate(util->getDateFromADIFDateString(data)); }
bool QSO::setForceInit(const QString& data) { return setForceInit(util->QStringToBool(data)); }
bool QSO::setHRDUpdateDate(const QString& data) { return setHRDUpdateDate(util->getDateFromADIFDateString(data)); }
bool QSO::setLoTWQSLRDate(const QString& data) { return setLoTWQSLRDate(util->getDateFromADIFDateString(data)); }
bool QSO::setLoTWQSLSDate(const QString& data) { return setLoTWQSLSDate(util->getDateFromADIFDateString(data)); }
bool QSO::setQRZCOMDate(const QString& data) { return setQRZCOMDate(util->getDateFromADIFDateString(data)); }
bool QSO::setQSLRDate(const QString& data) { return setQSLRDate(util->getDateFromADIFDateString(data)); }
bool QSO::setQSLSDate(const QString& data) { return setQSLSDate(util->getDateFromADIFDateString(data)); }
bool QSO::setDate(const QString& data) { return setDate(util->getDateFromADIFDateString(data)); }
bool QSO::setDateOff(const QString& data) { return setDateOff(util->getDateFromADIFDateString(data)); }
bool QSO::setQSORandom(const QString& data) { return setQSORandom(util->QStringToBool(data)); }
bool QSO::setSilentKey(const QString& data) { return setSilentKey(util->QStringToBool(data)); }
bool QSO::setSwl(const QString& data) { return setSwl(util->QStringToBool(data)); }
bool QSO::setTimeOff(const QString& data) { return setTimeOff(util->getTimeFromADIFTimeString(data)); }
bool QSO::setTimeOn(const QString& data) { return setTimeOn(util->getTimeFromADIFTimeString(data)); }

bool QSO::setLoTWQSLRDate2(const QString& data) {
    //qDebug() << "QSO::setData: APP_LOTW_RXQSL: " << data  << QT_ENDL;
    setLoTWQSL_RCVD("Y");
    return setLoTWQSLRDate(util->getDateFromLoTWQSLDateString(data));
}
bool QSO::setLoTWQSLSDate1(const QString& data) {
    //qDebug() << "QSO::setData: APP_LOTW_RXQSO: " << data  << QT_ENDL;
    setLoTWQSL_SENT("Y");
    return setLoTWQSLSDate(util->getDateFromLoTWQSLDateString(data));
}
bool QSO::setLoTWQSLSDate2(const QString& data) {
    //qDebug() << "QSO::setData: APP_LoTW_QSO_TIMESTAMP: " << data  << QT_ENDL;
    setLoTWQSL_SENT("Y");
    return setLoTWQSLSDate(util->getDateFromLoTWQSLDateString(data));
}

QHash<QString, decltype(std::mem_fn(&QSO::setSig))> QSO::SetDataHash;
void QSO::InitializeHash() {
    SetDataHash = { 
        {"ADDRESS", decltype(std::mem_fn(&QSO::setSig))(&QSO::setAddress)},
        {"AGE", decltype(std::mem_fn(&QSO::setSig))(&QSO::setAge)},
        {"A_INDEX", decltype(std::mem_fn(&QSO::setSig))(&QSO::setA_Index)},
        {"ANT_AZ", decltype(std::mem_fn(&QSO::setSig))(&QSO::setAnt_az)},
        {"ANT_EL", decltype(std::mem_fn(&QSO::setSig))(&QSO::setAnt_el)},
        {"ANT_PATH", decltype(std::mem_fn(&QSO::setSig))(&QSO::setAnt_Path)},
        {"ARRL_SECT", decltype(std::mem_fn(&QSO::setSig))(&QSO::setARRL_Sect)},
        {"AWARD_SUBMITTED", decltype(std::mem_fn(&QSO::setSig))(&QSO::setAwardSubmitted)},
        {"AWARD_GRANTED", decltype(std::mem_fn(&QSO::setSig))(&QSO::setAwardGranted)},
        {"BAND", decltype(std::mem_fn(&QSO::setSig))(&QSO::setBand)},
        {"BAND_RX", decltype(std::mem_fn(&QSO::setSig))(&QSO::setBandRX)},
        {"CALL", decltype(std::mem_fn(&QSO::setSig))(&QSO::setCall)},
        {"CHECK", decltype(std::mem_fn(&QSO::setSig))(&QSO::setCheck)},
        {"CLASS", decltype(std::mem_fn(&QSO::setSig))(&QSO::setClase)},
        {"CLUBLOG_QSO_UPLOAD_DATE", decltype(std::mem_fn(&QSO::setSig))(&QSO::setClublogQSOUpdateDate)},
        {"CLUBLOG_QSO_UPLOAD_STATUS", decltype(std::mem_fn(&QSO::setSig))(&QSO::setClubLogStatus)},
        {"CNTY", decltype(std::mem_fn(&QSO::setSig))(&QSO::setCounty)},
        {"COMMENT", decltype(std::mem_fn(&QSO::setSig))(&QSO::setComment)},
        {"CONT", decltype(std::mem_fn(&QSO::setSig))(&QSO::setContinent)},
        {"CONTACTED_OP", decltype(std::mem_fn(&QSO::setSig))(&QSO::setContactedOperator)},
        {"CONTEST_ID", decltype(std::mem_fn(&QSO::setSig))(&QSO::setContestID)},
        {"COUNTRY", decltype(std::mem_fn(&QSO::setSig))(&QSO::setCountry)},
        {"CQZ", decltype(std::mem_fn(&QSO::setSig))(&QSO::setCQZone)},
        {"CREDIT_SUBMITTED", decltype(std::mem_fn(&QSO::setSig))(&QSO::setCreditSubmitted)},
        {"CREDIT_GRANTED", decltype(std::mem_fn(&QSO::setSig))(&QSO::setCreditGranted)},
        {"DARC_DOK", decltype(std::mem_fn(&QSO::setSig))(&QSO::setDarcDok)},
        {"DISTANCE", decltype(std::mem_fn(&QSO::setSig))(&QSO::setDistance)},
        {"DXCC", decltype(std::mem_fn(&QSO::setSig))(&QSO::setDXCC)},
        {"EMAIL", decltype(std::mem_fn(&QSO::setSig))(&QSO::setEmail)},
        {"EQ_CALL", decltype(std::mem_fn(&QSO::setSig))(&QSO::setOwnerCallsign)},
        {"EQSL_QSLRDATE", decltype(std::mem_fn(&QSO::setSig))(&QSO::setEQSLQSLRDate)},
        {"EQSL_QSLSDATE", decltype(std::mem_fn(&QSO::setSig))(&QSO::setEQSLQSLSDate)},
        {"EQSL_QSL_RCVD", decltype(std::mem_fn(&QSO::setSig))(&QSO::setEQSLQSL_RCVD)},
        {"EQSL_QSL_SENT", decltype(std::mem_fn(&QSO::setSig))(&QSO::setEQSLQSL_SENT)},
        {"FISTS", decltype(std::mem_fn(&QSO::setSig))(&QSO::setFists)},
        {"FISTS_CC", decltype(std::mem_fn(&QSO::setSig))(&QSO::setFistsCC)},
        {"FORCE_INIT", decltype(std::mem_fn(&QSO::setSig))(&QSO::setForceInit)},
        {"FREQ", decltype(std::mem_fn(&QSO::setSig))(&QSO::setFreqTX)},
        {"FREQ_RX", decltype(std::mem_fn(&QSO::setSig))(&QSO::setFreqRX)},
        {"GRIDSQUARE", decltype(std::mem_fn(&QSO::setSig))(&QSO::setGridSquare)},
        {"GUEST_OP", decltype(std::mem_fn(&QSO::setSig))(&QSO::setOperatorCallsign)},
        {"HRDLOG_QSO_UPLOAD_DATE", decltype(std::mem_fn(&QSO::setSig))(&QSO::setHRDUpdateDate)},
        {"HRDLOG_QSO_UPLOAD_STATUS", decltype(std::mem_fn(&QSO::setSig))(&QSO::setHRDLogStatus)},
        {"IOTA", decltype(std::mem_fn(&QSO::setSig))(&QSO::setIOTA)},
        {"IOTA_ISLAND_ID", decltype(std::mem_fn(&QSO::setSig))(&QSO::setIotaID)},
        {"ITUZ", decltype(std::mem_fn(&QSO::setSig))(&QSO::setItuZone)},
        {"K_INDEX", decltype(std::mem_fn(&QSO::setSig))(&QSO::setK_Index)},
        {"LAT", decltype(std::mem_fn(&QSO::setSig))(&QSO::setLatitude)},
        {"LON", decltype(std::mem_fn(&QSO::setSig))(&QSO::setLongitude)},
        {"LOTW_QSLRDATE", decltype(std::mem_fn(&QSO::setSig))(&QSO::setLoTWQSLRDate)},
        {"LOTW_QSLSDATE", decltype(std::mem_fn(&QSO::setSig))(&QSO::setLoTWQSLSDate)},
        {"LOTW_QSL_RCVD", decltype(std::mem_fn(&QSO::setSig))(&QSO::setLoTWQSL_RCVD)},
        {"LOTW_QSL_SENT", decltype(std::mem_fn(&QSO::setSig))(&QSO::setEQSLQSL_SENT)},
        {"MAX_BURSTS", decltype(std::mem_fn(&QSO::setSig))(&QSO::setMaxBursts)},
        {"MODE", decltype(std::mem_fn(&QSO::setSig))(&QSO::setMode)},
        {"MS_SHOWER", decltype(std::mem_fn(&QSO::setSig))(&QSO::setMsShower)},
        {"MY_ANTENNA", decltype(std::mem_fn(&QSO::setSig))(&QSO::setMyAntenna)},
        {"MY_ARRL_SECT", decltype(std::mem_fn(&QSO::setSig))(&QSO::setMyArrlSect)},
        {"MY_CITY", decltype(std::mem_fn(&QSO::setSig))(&QSO::setMyCity)},
        {"MY_CNTY", decltype(std::mem_fn(&QSO::setSig))(&QSO::setMyCounty)},
        {"MY_COUNTRY", decltype(std::mem_fn(&QSO::setSig))(&QSO::setMyCountry)},
        {"MY_CQ_ZONE", decltype(std::mem_fn(&QSO::setSig))(&QSO::setMyCQZone)},
        {"MY_DXCC", decltype(std::mem_fn(&QSO::setSig))(&QSO::setMyDXCC)},
        {"MY_FISTS", decltype(std::mem_fn(&QSO::setSig))(&QSO::setMyFists)},
        {"MY_GRIDSQUARE", decltype(std::mem_fn(&QSO::setSig))(&QSO::setMyGridSquare)},
        {"MY_IOTA", decltype(std::mem_fn(&QSO::setSig))(&QSO::setMyIOTA)},
        {"MY_IOTA_ISLAND_ID", decltype(std::mem_fn(&QSO::setSig))(&QSO::setMyIotaID)},
        {"MY_ITU_ZONE", decltype(std::mem_fn(&QSO::setSig))(&QSO::setMyITUZone)},
        {"MY_LAT", decltype(std::mem_fn(&QSO::setSig))(&QSO::setMyLatitude)},
        {"MY_LON", decltype(std::mem_fn(&QSO::setSig))(&QSO::setMyLongitude)},
        {"MY_NAME", decltype(std::mem_fn(&QSO::setSig))(&QSO::setMyName)},
        {"MY_POSTAL_CODE", decltype(std::mem_fn(&QSO::setSig))(&QSO::setMyPostalCode)},
        {"MY_RIG", decltype(std::mem_fn(&QSO::setSig))(&QSO::setMyRig)},
        {"MY_SIG", decltype(std::mem_fn(&QSO::setSig))(&QSO::setMySig)},
        {"MY_SIG_INFO", decltype(std::mem_fn(&QSO::setSig))(&QSO::setMySigInfo)},
        {"MY_SOTA_REF", decltype(std::mem_fn(&QSO::setSig))(&QSO::setMySOTA_REF)},
        {"MY_STATE", decltype(std::mem_fn(&QSO::setSig))(&QSO::setMyState)},
        {"MY_STREET", decltype(std::mem_fn(&QSO::setSig))(&QSO::setMyStreet)},
        {"MY_USACA_COUNTIES", decltype(std::mem_fn(&QSO::setSig))(&QSO::setMyUsacaCounties)},
        {"MY_VUCC_GRIDS", decltype(std::mem_fn(&QSO::setSig))(&QSO::setMyVUCCGrids)},
        {"MY_WWFF_REF", decltype(std::mem_fn(&QSO::setSig))(&QSO::setMyWwffRef)},
        {"NAME", decltype(std::mem_fn(&QSO::setSig))(&QSO::setName)},
        {"NOTES", decltype(std::mem_fn(&QSO::setSig))(&QSO::setNotes)},
        {"NR_BURSTS", decltype(std::mem_fn(&QSO::setSig))(&QSO::setNrBursts)},
        {"NR_PINGS", decltype(std::mem_fn(&QSO::setSig))(&QSO::setNrPings)},
        {"OPERATOR", decltype(std::mem_fn(&QSO::setSig))(&QSO::setOperatorCallsign)},
        {"OWNER_CALLSIGN", decltype(std::mem_fn(&QSO::setSig))(&QSO::setOwnerCallsign)},
        {"PFX", decltype(std::mem_fn(&QSO::setSig))(&QSO::setPrefix)},
        {"PRECEDENCE", decltype(std::mem_fn(&QSO::setSig))(&QSO::setPrecedence)},
        {"PROP_MODE", decltype(std::mem_fn(&QSO::setSig))(&QSO::setPropMode)},
        {"PUBLIC_KEY", decltype(std::mem_fn(&QSO::setSig))(&QSO::setPublicKey)},
        {"QRZCOM_QSO_UPLOAD_DATE", decltype(std::mem_fn(&QSO::setSig))(&QSO::setQRZCOMDate)},
        {"QRZCOM_QSO_UPLOAD_STATUS", decltype(std::mem_fn(&QSO::setSig))(&QSO::setQRZCOMStatus)},
        {"QSLMSG", decltype(std::mem_fn(&QSO::setSig))(&QSO::setQSLMsg)},
        {"QSLRDATE", decltype(std::mem_fn(&QSO::setSig))(&QSO::setQSLRDate)},
        {"QSLSDATE", decltype(std::mem_fn(&QSO::setSig))(&QSO::setQSLSDate)},
        {"QSL_RCVD", decltype(std::mem_fn(&QSO::setSig))(&QSO::setQSL_RCVD)},
        {"QSL_RCVD_VIA", decltype(std::mem_fn(&QSO::setSig))(&QSO::setQSLRecVia)},
        {"QSL_SENT", decltype(std::mem_fn(&QSO::setSig))(&QSO::setQSL_SENT)},
        {"QSL_SENT_VIA", decltype(std::mem_fn(&QSO::setSig))(&QSO::setQSLSenVia)},
        {"QSL_VIA", decltype(std::mem_fn(&QSO::setSig))(&QSO::setQSLVia)},
        {"QSO_COMPLETE", decltype(std::mem_fn(&QSO::setSig))(&QSO::setQSOComplete)},
        {"QSO_DATE", decltype(std::mem_fn(&QSO::setSig))(&QSO::setDate)},
        {"QSO_DATE_OFF", decltype(std::mem_fn(&QSO::setSig))(&QSO::setDateOff)},
        {"QSO_RANDOM", decltype(std::mem_fn(&QSO::setSig))(&QSO::setQSORandom)},
        {"QTH", decltype(std::mem_fn(&QSO::setSig))(&QSO::setQTH)},
        {"REGION", decltype(std::mem_fn(&QSO::setSig))(&QSO::setRegion)},
        {"RIG", decltype(std::mem_fn(&QSO::setSig))(&QSO::setRig)},
        {"RST_RCVD", decltype(std::mem_fn(&QSO::setSig))(&QSO::setRSTRX)},
        {"RST_SENT", decltype(std::mem_fn(&QSO::setSig))(&QSO::setRSTTX)},
        {"RX_PWR", decltype(std::mem_fn(&QSO::setSig))(&QSO::setRXPwr)},
        {"SAT_MODE", decltype(std::mem_fn(&QSO::setSig))(&QSO::setSatMode)},
        {"SAT_NAME", decltype(std::mem_fn(&QSO::setSig))(&QSO::setSatName)},
        {"SFI", decltype(std::mem_fn(&QSO::setSig))(&QSO::setSFI)},
        {"SIG", decltype(std::mem_fn(&QSO::setSig))(&QSO::setSig)},
        {"SIG_INFO", decltype(std::mem_fn(&QSO::setSig))(&QSO::setSigInfo)},
        {"SILENT_KEY", decltype(std::mem_fn(&QSO::setSig))(&QSO::setSilentKey)},
        {"SKCC", decltype(std::mem_fn(&QSO::setSig))(&QSO::setSkcc)},
        {"SOTA_REF", decltype(std::mem_fn(&QSO::setSig))(&QSO::setSOTA_REF)},
        {"SRX", decltype(std::mem_fn(&QSO::setSig))(&QSO::setSrx)},
        {"SRX_STRING", decltype(std::mem_fn(&QSO::setSig))(&QSO::setSrxString)},
        {"STATE", decltype(std::mem_fn(&QSO::setSig))(&QSO::setState)},
        {"STATION_CALLSIGN", decltype(std::mem_fn(&QSO::setSig))(&QSO::setStationCallsign)},
        {"STX", decltype(std::mem_fn(&QSO::setSig))(&QSO::setStx)},
        {"STX_STRING", decltype(std::mem_fn(&QSO::setSig))(&QSO::setStxString)},
        {"SUBMODE", decltype(std::mem_fn(&QSO::setSig))(&QSO::setSubmode)},
        {"SWL", decltype(std::mem_fn(&QSO::setSig))(&QSO::setSwl)},
        {"TEN_TEN", decltype(std::mem_fn(&QSO::setSig))(&QSO::setTenTen)},
        {"TIME_OFF", decltype(std::mem_fn(&QSO::setSig))(&QSO::setTimeOff)},
        {"TIME_ON", decltype(std::mem_fn(&QSO::setSig))(&QSO::setTimeOn)},
        {"TX_PWR", decltype(std::mem_fn(&QSO::setSig))(&QSO::setTXPwr)},
        {"UKSMG", decltype(std::mem_fn(&QSO::setSig))(&QSO::setUksmg)},
        {"USACA_COUNTIES", decltype(std::mem_fn(&QSO::setSig))(&QSO::setUsacaCounties)},
        {"VE_PROV", decltype(std::mem_fn(&QSO::setSig))(&QSO::setVeProv)},
        {"VUCC_GRIDS", decltype(std::mem_fn(&QSO::setSig))(&QSO::setVUCCGrids)},
        {"WEB", decltype(std::mem_fn(&QSO::setSig))(&QSO::setWeb)},
        {"WWFF_REF", decltype(std::mem_fn(&QSO::setSig))(&QSO::setWwffRef)},
        {"APP_LOTW_RXQSL", decltype(std::mem_fn(&QSO::setSig))(&QSO::setLoTWQSLRDate2)},
        {"APP_LOTW_RXQSO", decltype(std::mem_fn(&QSO::setSig))(&QSO::setLoTWQSLSDate1)},
        {"APP_LOTW_QSO_TIMESTAMP", decltype(std::mem_fn(&QSO::setSig))(&QSO::setLoTWQSLSDate2)}
    };
    return;




}



// SET DATA ----------------------------------------------------------------------------------
bool QSO::setData(const QString &_adifPair)
{
    logEvent (Q_FUNC_INFO, "Start", Debug);
    //qDebug() << "QSO::setData: " << _adifPair << QT_ENDL;
    QStringList d;
    d.clear();
    d << util->getValidADIFFieldAndData(_adifPair);
    if (d.length()!=2)
    {
        logEvent (Q_FUNC_INFO, "END - ADIF not valid", Debug);
        return false;
    }
    //qDebug() << "QSO::setData: " << d.at(0) << "/" << d.at(1) << QT_ENDL;

    QString field = d.at(0).toUpper();
    QString data = d.at(1);

    if (SetDataHash.empty()) {
        InitializeHash();
    }
    if (SetDataHash.contains(field)) {
        (*SetDataHash.find(field))(this,data);
    }

    logEvent (Q_FUNC_INFO, "END", Debug);
    return true;
}
