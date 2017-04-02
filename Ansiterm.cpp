/*
Ansiterm.cpp -- an Arduino library that simplifies using the ANSI terminal
control escape sequences. This allows your code to  position text exactly in the
terminal, to add colour and other effects. To use Ansiterm, an ANSI terminal must
be connected to the Arduino's serial port. The terminal built into the Arduino
IDE does not respond to the ANSI codes, but most MacOs and Linux terminals do.
In Windows, I read that Hyperterm responds to ANSI codes. Realterm responds to most
codes, but will not change the color of the foreground.

The accompanying example file illustrates the library's use.

Copyright (c) 2009 Bruce Robertson, VE9QRP. All rights reserved.

This library is free software; you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the Free
Software Foundation; either version 2.1 of the License, or (at your option)
any later version.

This library is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more
details.

You should have received a copy of the GNU Lesser General Public License along
with this library; if not, write to the Free Software Foundation, Inc., 51
Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

The latest version of this software is available at
*/

#include "Arduino.h"
#include "Ansiterm.h"

void Ansiterm::home()
{
  preamble();
  _stream.write('H');
}

void Ansiterm::xy(int x, int y)
{
  preamble();
  _stream.print(y,DEC);
  _stream.write(';');
  _stream.print(x, DEC);
  _stream.write('H');
}

void Ansiterm::up(int x)
{
  preambleAndNumberAndValue(x,'A');
}

void Ansiterm::down(int x)
{
  preambleAndNumberAndValue(x,'B');
}

void Ansiterm::forward(int x)
{
  preambleAndNumberAndValue(x,'C');
}

void Ansiterm::backward(int x)
{
  preambleAndNumberAndValue(x,'D');
}

void Ansiterm::eraseLine()
{
  preamble();
  _stream.write('2');
  _stream.write('K');
}

void Ansiterm::eraseScreen()
{
  preamble();
  _stream.write('1');
  _stream.write('J');
}

void Ansiterm::setBackgroundColor(int color)
{
  setAttribute(color + 40);
}

void Ansiterm::setForegroundColor(int color)
{
  setAttribute(color + 30);
}

void Ansiterm::boldOn()
{
  setAttribute(BOLD_ON);
}

void Ansiterm::boldOff()
{
  setAttribute(BOLD_OFF);
}

void Ansiterm::italicsOn()
{
  setAttribute(ITALICS_ON);
}

void Ansiterm::italicsOff()
{
  setAttribute(ITALICS_OFF);
}

void Ansiterm::underlineOn()
{
  setAttribute(UNDERLINE_ON);
}

void Ansiterm::underlineOff()
{
  setAttribute(UNDERLINE_OFF);
}

void Ansiterm::strikethroughOn()
{
  setAttribute(STRIKETHROUGH_ON);
}

void Ansiterm::strikethroughOff()
{
  setAttribute(STRIKETHROUGH_OFF);
}

void Ansiterm::inverseOn()
{
  setAttribute(INVERSE_ON);
}

void Ansiterm::inverseOff()
{
  setAttribute(INVERSE_OFF);
}

void Ansiterm::reset()
{
  setAttribute(RESET);
}

void Ansiterm::defaultBackground()
{
  setAttribute(DEFAULT_BACKGROUND);
}

void Ansiterm::defaultForeground()
{
  setAttribute(DEFAULT_FOREGROUND);
}

void Ansiterm::fill(int x1, int y1, int x2, int y2)
{
  for (int x = x1; x <= x2; x++)
  {
    for (int y = y1; y <= y2; y++)
    {
      xy(x,y);
      _stream.print(' ');
    }
  }
}

/* private functions */
void Ansiterm::preamble()
{
  _stream.write(ESCAPE);
  _stream.write(BRACE);
}

void Ansiterm::preambleAndNumberAndValue(int x, char v)
{
  preamble();
  _stream.print(x,DEC);
  _stream.write(v);
}

void Ansiterm::setAttribute(int a)
{
  preambleAndNumberAndValue(a, 'm');
}

void Ansiterm::deviceStatusReport()
{
  preambleAndNumberAndValue(6, 'n');
}

unsigned long Ansiterm::detectSize(unsigned long timeout)
{
  xy(900,900);
  deviceStatusReport();
  timeout += millis();
  unsigned char ncount = 0;
  unsigned int num = 0;
  unsigned char wasdigit = false;
  char c = 0;
  maxX = 0;
  maxY = 0;
  while (!isalpha(c) && millis() < timeout) {
    if (_stream.available() > 0) {
      c = _stream.read();
      if (isdigit(c)) {
        num *= 10;
        num += c - '0';
        wasdigit = true;
      } 
      else {
        if (wasdigit) {
          wasdigit = false;
          ++ncount;
          switch (ncount) {
          case 1:
            maxY = num;
            break;
          case 2:
            maxX = num;
            break;
          }
          num = 0;
        }
      }
    }
  }
  return timeout - millis();
}

unsigned int Ansiterm::getMaxX() {
	return maxX;
}

unsigned int Ansiterm::getMaxY() {
	return maxY;
}

