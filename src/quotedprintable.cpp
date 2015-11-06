/*
  Copyright (c) 2011-2012 - Tőkés Attila
  Copyright (C) 2015 Daniel Nicoletti <dantti12@gmail.com>

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  See the LICENSE file for more details.
*/

#include "quotedprintable.h"

QString QuotedPrintable::encode(const QByteArray &input)
{
    QString output;

    char byte;
    const char hex[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

    for (int i = 0; i < input.length() ; ++i) {
        byte = input[i];

        if ((byte == 0x20) || ((byte >= 33) && (byte <= 126) && (byte != 61))) {
            // TODO check if QLatin1Char if fine here
            output.append(QLatin1Char(byte));
        } else {
            // TODO check if QLatin1Char if fine here
            output.append(QLatin1Char('='));
            output.append(QLatin1Char(hex[((byte >> 4) & 0x0F)]));
            output.append(QLatin1Char(hex[(byte & 0x0F)]));
        }
    }

    return output;
}

QByteArray QuotedPrintable::decode(const QString &input)
{
    //                    0  1  2  3  4  5  6  7  8  9  :  ;  <  =  >  ?  @  A   B   C   D   E   F
    const int hexVal[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0, 0, 0, 0, 0, 0, 10, 11, 12, 13, 14, 15};

    QByteArray output;

    for (int i = 0; i < input.length(); ++i)
    {
        if (input.at(i).toLatin1() == '=')
        {
            output.append((hexVal[input.at(i + 1).toLatin1() - '0'] << 4) + hexVal[input.at(i + 2).toLatin1() - '0']);
            i += 2;
        }
        else
        {
            output.append(input.at(i).toLatin1());
        }
    }

    return output;
}