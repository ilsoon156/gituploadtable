#include <eosio/eosio.hpp>
#include <eosio/asset.hpp>

using namespace eosio;

CONTRACT inlinedummy: public contract {
    public:
    using contract::contract;

    ACTION dummy(name user) {
        require_auth(user);

        print("dummy");

        action(
            //permossoion,
            permission_level(user, "active"_n),
            //contract name,
            get_self(),
            //action name,
            "dummytwo"_n,
            //parameters
            std::make_tuple(user)
        ).send();
    }
    
    ACTION dummytwo(name user) {
        require_auth(user);

        print("dummytwo, ", user);
    }

    [[eosio::on_notify("eosio.token::transfer")]]
    void ontransfer(name from, name to, asset quantity, std::string memo) {
        if(from == get_self()) {
            inautokeys Receiver(get_self(), get_self().value);
        
            Receiver.emplace(from, [&](auto& row) {
                row.balance = quantity;
                row.user = to;
                row.mykeys = Receiver.available_primary_key();
            });
        }else if(to == get_self()) {
            outautokeys Sender(get_self(), get_self().value);
            
            Sender.emplace(to, [&](auto& row) {
                row.balance = quantity;
                row.user = from;
                row.mykeys = Sender.available_primary_key();
            });
        }
    }

    private:
        TABLE extra_autokey {
            uint64_t mykeys;
            asset balance;
            name user;

            uint64_t primary_key() const { return user.value; }
        };

        typedef multi_index<"autokeys1"_n, extra_autokey> inautokeys;
        typedef multi_index<"autokeys2"_n, extra_autokey> outautokeys;

};
