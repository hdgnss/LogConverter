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

#include <QFile>
#include <QProcess>
#include <QRegularExpression>


int LogConverter::ConvertLog(QString input, QString output)
{
    QRegularExpression mNmeaRegular("(\\$[A-Z]{4,8},.*\\*[0-9a-fA-F]{2,2}$)");
    QRegularExpressionMatch mNmeaMatch;

    QFile mInputFile(input);
    if (!mInputFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Input file can not open\n";
        return -1;
    }

    QFile mOutputFile(output);
    if (!mOutputFile.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug() << "Output file can not open\n";
        mInputFile.close(); // Close the input file if the output file cannot be opened
        return -2;
    }

    QTextStream mInputStream(&mInputFile);
    QTextStream mOutputStream(&mOutputFile);

    while (!mInputStream.atEnd()) {
        mNmeaMatch = mNmeaRegular.match(mInputStream.readLine());
        if (mNmeaMatch.hasMatch()) {
            mOutputStream  << mNmeaMatch.captured(0) << "\n";
        }
    }

    mInputFile.close();
    mOutputFile.close();
    return 0;
}

int LogConverter::ConvertLogGrep(QString input, QString output)
{
    QProcess *process = new QProcess();
    process->setProgram("grep");
    process->setArguments({"-E", "-o", "(\\$[A-Z]{4,8},.*\\*[0-9a-fA-F]{2,2})", input});
    process->setStandardOutputFile(output);
    process->start();
    process->waitForFinished();
    return 0;
}

QString LogConverter::Version(void)
{
    return QString::fromUtf8(PROJECT_VER);
}