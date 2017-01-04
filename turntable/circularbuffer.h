#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H
#include <QByteArray>

class CircularBuffer
{
public:
    CircularBuffer(int size);

    qint64 bytesAvailable() const { return bytesToRead; }
    void flush();
    bool getChar(char* c);
    bool putChar(char c);
    QByteArray readAll();
    int size() const { return bufferSize; }

private:
    QByteArray buffer;
    int bufferSize;
    int readPos;
    int writePos;
    int bytesToRead;
};

#endif // CIRCULARBUFFER_H
