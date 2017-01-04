#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H
#include <QByteArray>

/*!
    \class CircularBuffer
    \brief The CircularBuffer class is a fixed sized circular buffer.

    This particular circular buffer implementation doesn't allow buffer overflow and
    will discard all new characters put with getChar().
*/
class CircularBuffer
{
public:
    CircularBuffer(int size);

    qint64 bytesAvailable() const { return bytesToRead; }

    //! Flushes all pointers and fills the buffer with zeros.
    void flush();

    bool getChar(char* c);

    bool putChar(char c);

    /*!
    \fn QByteArray readAll()

    Reads all available characters in the buffer in an QByteArray with the appropriate length.
    */
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
