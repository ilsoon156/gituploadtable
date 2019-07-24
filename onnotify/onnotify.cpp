#include <eosio/eosio.hpp>
#include <eosio/asset.hpp>

using namespace eosio;

CONTRACT onnotify: public contract {
    public:
    using contract::contract;

    ACTION dummy() {}

    [[eosio::on_notify("eosio.token::transfer")]]
    void ontransfer(name from, name to, asset quantity, std::string memo) {
    if(from == get_self()) {
        receiver Receiver(get_self(), get_self().value);
        auto itr = Receiver.find(to.value);
        if(itr == Receiver.end()) {
            Receiver.emplace(from, [&](auto& row) {
            row.balance = quantity;
            row.user = to;
            
        });
    } else {
        auto itr = Receiver.begin();
            Receiver.modify(itr, to, [&](auto& row) {
            row.balance += quantity;

            });
        }
        } else {
            sender Sender(get_self(), get_self().value);
            auto itr = Sender.find(from.value);
            if(itr == Sender.end()) {
            Sender.emplace(to, [&](auto& row) {
                row.user = from;
                row.balance = quantity;
            });
        } else {
            Sender.modify(itr, to, [&](auto& row) {
            row.balance += quantity;
        });
        }
    }
    }
    private:
        TABLE tlist {
            asset balance;
            name user;

            uint64_t primary_key() const { return user.value; }
        };

        typedef multi_index<"list12"_n, tlist> sender;
        typedef multi_index<"list23"_n, tlist> receiver;
};