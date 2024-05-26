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
#include <cstdint>

// #include "Kitchen.hpp"

namespace plz {

    class Packet
    {
        public:
            Packet() = default;
            Packet(const std::vector<std::byte>& bytes);
            ~Packet() = default;

            /**
             * @brief Gets the total size of the received packet.
             * @warning This does not deminish with reading.
            */
            std::size_t size() const { return this->_size; }
            /**
             * @brief Gets the remaining bytes in the packet.
             * It accounts for read bytes.
            */
            std::size_t remains() const { return this->_size - this->_pos; }
            /**
             * @brief Gets the current reading position
            */
            std::uint32_t pos() const { return this->_pos; }
            /**
             * @brief Appends new data to the packer
            */
            void append(const void *data, std::size_t size);
            /**
             * @brief The raw data contained in the packet.
             * @warning Does NOT account for read bytes.
            */
            const void *raw() const;
            /**
             * @brief Tells if a packet operation failed.
            */
           bool fail() const { return this->_fail; }

            Packet& operator<<(bool data);
            Packet& operator<<(char data);
            Packet& operator<<(std::uint8_t data);
            Packet& operator<<(int data);
            Packet& operator<<(std::uint32_t data);
            // Packet& operator<<(int64_t data);
            Packet& operator<<(std::size_t data);
            Packet& operator<<(const char *data);
            Packet& operator<<(const std::string& data);
            // Packet& operator<<(const plz::KitchenDatas& data);

            Packet& operator>>(bool& data);
            Packet& operator>>(char& data);
            Packet& operator>>(int& data);
            Packet& operator>>(std::uint32_t& data);
            // Packet& operator>>(int64_t& data);
            Packet& operator>>(std::size_t& data);
            Packet& operator>>(char *data);
            Packet& operator>>(std::string& data);
            // Packet& operator>>(KitchenDatas& data);

        protected:
        private:
            bool _checkSize(std::size_t size);
            std::uint32_t _pos = 0;
            std::size_t _size = 0;
            std::vector<std::byte> _data = {};
            bool _fail = false;
    };

}
