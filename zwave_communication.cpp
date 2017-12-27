#include "zwave_communication.h"

ZwaveCommunicationClass::ZwaveCommunicationClass(byte* command, byte* value)
{
    commandPtr = command;
    valuePtr = value;
}

void ZwaveCommunicationClass::SendCommandValue(byte command, byte value)
{
    *commandPtr = command;
    *valuePtr = value;
    zunoSendReport(ZUNO_REPORT_ZTXCOMMAND);
    zunoSendReport(ZUNO_REPORT_ZTXVALUE);
}

void ZwaveCommunicationClass::ReportTemperature()
{
    zunoSendReport(ZUNO_REPORT_TEMP);
}

void ZwaveCommunicationClass::ReportHumidity()
{
    zunoSendReport(ZUNO_REPORT_HUMIDITY);
}
