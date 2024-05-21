/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Packet
*/

#pragma once

#include <cstring>
#include <string>
#include <vector>

namespace plz {

    class Packet
    {
        public:
            Packet() = default;
            Packet(const std::vector<std::byte>& bytes);
            ~Packet() = default;

            std::size_t size() const { return this->_size; }
            std::uint32_t pos() const { return this->_pos; }
            void append(const void *data, std::size_t size);
            const void *raw() const;

            Packet& operator<<(bool data);
            Packet& operator<<(char data);
            Packet& operator<<(std::uint8_t data);
            Packet& operator<<(int data);
            Packet& operator<<(std::uint32_t data);
            Packet& operator<<(std::size_t data);
            Packet& operator<<(const char *data);
            Packet& operator<<(const std::string& data);

            Packet& operator>>(bool& data);
            Packet& operator>>(char& data);
            Packet& operator>>(int& data);
            Packet& operator>>(std::uint32_t& data);
            Packet& operator>>(std::size_t& data);
            Packet& operator>>(char *data);
            Packet& operator>>(std::string& data);

        protected:
        private:
            bool _checkSize(std::size_t size);
            std::uint32_t _pos = 0;
            std::size_t _size = 0;
            std::vector<std::byte> _data = {};
    };

    class IPacketable
    {
        public:
            ~IPacketable() = default;

            virtual Packet pack() const = 0;
            virtual void unpack(const Packet& packer) = 0;
        protected:
        private:
    };

}
