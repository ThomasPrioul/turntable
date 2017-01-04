#include "circularbuffer.h"

CircularBuffer::CircularBuffer(int size) :
    buffer(size, 0),
    bufferSize(size),
    readPos(0),
    writePos(0),
    bytesToRead(0)
{

}

void CircularBuffer::flush()
{
    bytesToRead = 0;
    writePos = 0;
    readPos = 0;
    buffer.fill(0);
}

bool CircularBuffer::getChar(char* c)
{
    if (bytesToRead) {
        *c = buffer[readPos++];
        bytesToRead--;

        if (readPos >= bufferSize)
            readPos = 0;

        return true;
    }

    return false;
}

bool CircularBuffer::putChar(char c)
{        
    if (bytesToRead < bufferSize) {
        buffer[writePos++] = c;
        bytesToRead++;

        if (writePos >= bufferSize)
            writePos = 0;

        return true;
    }

    return false;
}

//QByteArray CircularBuffer::readAll()
//{
//    QByteArray dataRead(bytesToRead, 0);
//    int insertPos = 0;

//    if (bytesToRead > (bufferSize - readPos)) {
//        dataRead = dataRead.replace(0, bufferSize - readPos - 1, buffer.constData() + readPos);
//        insertPos += (bufferSize - readPos - 1);
//        bytesToRead -= (bufferSize - readPos - 1);
//        readPos = 0;
//    }

//    dataRead = dataRead.replace(insertPos, bytesToRead, buffer.constData() + readPos);
//    readPos += bytesToRead;
//    bytesToRead = 0;
//}

QByteArray CircularBuffer::readAll()
{
    QByteArray dataRead(bytesToRead, 0);
    char c;
    int i = 0;

    while (getChar(&c)) {
        dataRead[i++] = c;
    }

    return dataRead;
}
