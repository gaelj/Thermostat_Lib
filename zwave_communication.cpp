#include "zwave_communication.h"

byte ztxCommand = 0;
byte ztxValue = 0;
byte zrxCommand = 0;
byte zrxValue = 0;

void ReportTXCommandValue(byte command, byte value)
{
    ztxCommand = command;
    ztxValue = value;
    zunoSendReport(ZUNO_REPORT_ZTXCOMMAND);
    zunoSendReport(ZUNO_REPORT_ZTXVALUE);
}

void ReportRXCommandValue(byte command, byte value)
{
    zrxCommand = command;
    zrxValue = value;
    zunoSendReport(ZUNO_REPORT_ZRXCOMMAND);
    zunoSendReport(ZUNO_REPORT_ZRXVALUE);
}

void ReportTemperature()
{
    zunoSendReport(ZUNO_REPORT_TEMP);
}

void ReportHumidity()
{
    zunoSendReport(ZUNO_REPORT_HUMIDITY);
}
