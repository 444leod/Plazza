/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Kitchen
*/

#pragma once

#include "IPizza.hpp"
#include "Ingredients.hpp"
#include "Fork.hpp"
#include "IpcTool.hpp"
#include "Packet.hpp"
#include "ThreadPool.hpp"

#include <cstdint>
#include <string>
#include <memory>
#include <vector>
#include <chrono>
#include <optional>

namespace plz {
    struct KitchenDatas {
        uint32_t pizzaiolos;
        uint32_t storage;
        plz::Ingredients ingredients;
        std::chrono::milliseconds idleTime;
    };

    class Kitchen {
        // Global
        public:
            Kitchen(uint32_t pizzaiolos, uint32_t restockTime);
            ~Kitchen();
            void setPid(int pid) { _pid = pid; }

            void initPipe(plz::ProcessSide side);
            uint32_t pizzaiolos() { return _pizzaiolosNumber; }
            uint32_t restockTime() { return _restockTime; }
            uint32_t id() { return _id; }
            void setFork(std::shared_ptr<plz::Fork> fork) { _fork = fork; }
            std::optional<plz::Packet> getPacket();
            void sendPacket(plz::Packet& packet);


        private:
            int _pid;
            static uint32_t _nextId;
            uint32_t _id = 0;
            std::shared_ptr<plz::Fork> _fork;
            std::shared_ptr<plz::IpcTool> _ipcTool;
            std::vector<std::shared_ptr<plz::Packet>> _packetsQueue = {};
            plz::ProcessSide _kitchenSide;

        // Reception side
        public:
            void queuePizza(std::shared_ptr<plz::IPizza> pizza);
            void close();
            void waitFork();
            bool _readForkInit();
            std::vector<std::shared_ptr<plz::Packet>>& getWaitingPackets();

        private:
            std::string _fetch();


        // Kitchen side
        public:
            void run();

        private:
            void _queueReceivedPacket();
            void _handlePackets();
            void _restockIngredients();
            void _pizzaioloPizzas();
            void _sendDisplayStatus();
            void _sendStatus();
            void _verifyClosing();
            void _spreadPizzas();

            uint32_t _pizzaiolosNumber = 0;
            uint32_t _restockTime = 0;
            uint32_t _availablePizzaiolos = 0;
            uint32_t _availableStorage = 0;
            std::vector<std::shared_ptr<plz::IPizza>> _pizzas = {};
            std::shared_ptr<plz::Ingredients> _ingredients = std::make_shared<plz::Ingredients>(5, 5, 5, 5, 5, 5, 5, 5 ,5);
            std::chrono::time_point<std::chrono::system_clock> _lastActivity;
            std::chrono::time_point<std::chrono::system_clock> _lastRestock;
            std::shared_ptr<ThreadPool> _threadPool;
            std::mutex _printMutex;
            std::mutex _activityMutex;
            bool _running = true;

    };
}

inline uint32_t plz::Kitchen::_nextId = 0;
