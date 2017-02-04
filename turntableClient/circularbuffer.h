#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H
#include <vector>
#include <string>

/*!
    \class CircularBuffer
    \brief The CircularBuffer class is a fixed sized circular buffer.

    This particular circular buffer implementation doesn't allow buffer overflow and
    will discard all new characters put with putChar().
*/
template <typename T>
class CircularBuffer
{
public:
    CircularBuffer(std::size_t size) : buffer(size), bufferSize(size), readPos(0), writePos(0), bytesToRead(0) {}

    size_t bytesAvailable() const { return bytesToRead; }
    bool empty() const { return bytesToRead == 0; }

    //! Flushes all pointers and fills the buffer with zeros.
    void flush()
    {
        bytesToRead = 0;
        writePos = 0;
        readPos = 0;
    }

    //! Gets an item if possible. Returns false if the buffer is empty.
    bool get(T* item)
    {
        if (bytesToRead) {
            *item = buffer[readPos++];
            bytesToRead--;

            if (readPos >= bufferSize)
                readPos = 0;

            return true;
        }

        return false;
    }

    //! Puts an item into the buffer. Returns false when the buffer is already full.
    bool put(T item)
    {
        if (bytesToRead < bufferSize) {
            buffer[writePos++] = item;
            bytesToRead++;

            if (writePos >= bufferSize)
                writePos = 0;

            return true;
        }

        return false;
    }

    //! Reads all available items in the buffer in a vector with the appropriate length.
    std::vector<T> readAll()
    {
        int i = 0;
        T item;
        std::vector<T> output(bytesToRead);

        while (get(&item)) {
            output[i++] = item;
        }

        //output[i] = 0;

        return output;
    }

    size_t size() const { return bufferSize; }

private:
    std::vector<T> buffer;
    size_t bufferSize;
    size_t readPos;
    size_t writePos;
    size_t bytesToRead;
};

#endif // CIRCULARBUFFER_H
