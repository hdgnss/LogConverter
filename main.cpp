 /*
 * Copyright (C) 2024 HDGNSS
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "config.h"
#include "logconverter.h"

#include <QDir>
#include <QList>
#include <QFileInfo>
#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>


int main(int argc, char *argv[])
{
    QCommandLineParser mCommandParser;

    QString mInput;
    QString mOutput;
    bool mGrep = false;
    int ret = -1;

    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName(PROJECT_NAME);
    QCoreApplication::setApplicationVersion(PROJECT_VER);

    mCommandParser.setApplicationDescription("GPS LOG TO NMEA");
    mCommandParser.addHelpOption();
    mCommandParser.addVersionOption();


    QCommandLineOption mInputOption(QStringList() << "i" << "input",
                                    QCoreApplication::translate("main", "Input GPS log file"),
                                    QCoreApplication::translate("main", "path"));
    mCommandParser.addOption(mInputOption);

    QCommandLineOption mOutputOption(QStringList() << "o" << "output",
                                    QCoreApplication::translate("main", "Output NMEA file"),
                                    QCoreApplication::translate("main", "path"));
    mCommandParser.addOption(mOutputOption);

    QCommandLineOption mGrepOption(QStringList() << "g" << "grep",
                                    QCoreApplication::translate("main", "Use grep"));
    mCommandParser.addOption(mGrepOption);

    mCommandParser.process(app);

    mGrep = mCommandParser.isSet(mGrepOption);

    if (!mCommandParser.isSet(mInputOption)){
        mCommandParser.showHelp(-1);
        return -1;
    }
    mInput = mCommandParser.value(mInputOption);
    QFileInfo mLogFileInfo(mInput);
   
    if (mCommandParser.isSet(mOutputOption)){
        mOutput = mCommandParser.value(mOutputOption);
    }
    else{
        QDir mLogDirectory(mLogFileInfo.absolutePath());
        mOutput  = mLogDirectory.absoluteFilePath(mLogFileInfo.baseName() + ".nmea");
    }

    LogConverter *mConvert = new LogConverter();

    if (mLogFileInfo.isFile()) {
        if(mGrep){
            ret = mConvert->ConvertLogGrep(mInput, mOutput);
        }
        else{
            ret = mConvert->ConvertLog(mInput, mOutput);
        }
    }

    return ret;
}

