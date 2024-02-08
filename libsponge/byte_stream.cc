#include "byte_stream.hh"

#include <algorithm>
#include <iterator>
#include <stdexcept>

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}


ByteStream::ByteStream(const size_t capacity):
    _data(), _cap(capacity), bytes_read_(0), bytes_written_(0), _end_input(false), _error(false) {}

size_t ByteStream::write(const std::string &data) {
    if(_end_input)
        return 0;
    size_t len = std::min(data.size(), remaining_capacity());
    bytes_written_ += len;
    for(size_t i = 0; i < len; i++)
        _data.push_back(data[i]);
    return len;
}

//! \param[in] len bytes will be copied from the output side of the buffer
std::string ByteStream::peek_output(const size_t len) const {
    size_t peek_bytes = std::min(len, _data.size());
    return std::string(_data.begin(), _data.begin() + peek_bytes);
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) {
    size_t pop_bytes = std::min(len, _data.size());
    bytes_read_ += pop_bytes;
    for(size_t i = 0; i < pop_bytes; i++)
        _data.pop_front();
}

void ByteStream::end_input() { _end_input = true; }

bool ByteStream::input_ended() const { return _end_input; }

size_t ByteStream::buffer_size() const { return _data.size(); }

bool ByteStream::buffer_empty() const { return _data.empty(); }

bool ByteStream::eof() const { return _data.empty() && _end_input; }

size_t ByteStream::bytes_written() const { return bytes_written_; }

size_t ByteStream::bytes_read() const { return bytes_read_; }

size_t ByteStream::remaining_capacity() const { return _cap - _data.size(); }
