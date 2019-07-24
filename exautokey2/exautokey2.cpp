#include <eosio/eosio.hpp>
#include <eosio/asset.hpp>

using namespace eosio;

CONTRACT exautokey2: public contract {
    public:
    using contract::contract;

    ACTION dummy() {}
    
    
    [[eosio::on_notify("eosio.token::transfer")]]
    void ontransfer(name from, name to, asset quantity, std::string memo) {
        if(from == get_self()) {
            inautokeys Receiver(get_self(), to.value);
            esall1 Receall(get_self(), to.value);
        
            Receiver.emplace(from, [&](auto& row) {
                row.balance = quantity;
                row.user = to;
                row.mykeys = Receiver.available_primary_key();
            });

            Receall.emplace(from, [&](auto& row) {
                row.scope = to.value;
            });
        }else if(to == get_self()) {
            outautokeys Sender(get_self(), from.value);
            esall2 Receall(get_self(), from.value);
            
            Sender.emplace(to, [&](auto& row) {
                row.balance = quantity;
                row.user = from;
                row.mykeys = Sender.available_primary_key();
            });

            Receall.emplace(to, [&](auto& row){
                row.scope = from.value;
            });
        }
    }

    ACTION eraseall() {

            inautokeys forErase1(get_self(), get_self().value);
            outautokeys forErase2(get_self(), get_self().value);
            auto itrerase1 = forErase1.begin();
            

            while(itrerase1 != forErase1.end()) {
                while(inautokeys != inautokeys.begin()) {
                    auto itr = forErase1.find(scope);
                    forErase1.erase(itr);
                };
            }

            auto itrerase2 = forErase2.begin();

            while(itrerase2 != forErase2.end()) {
                while(outautokeys != outautokeys.begin()) {
                    auto itr = forErase2.find(scope);
                    forErase2.erase(itr);
                };
            }

        print("Erase All Complete");
    }

    private:
        TABLE extra_autokey {
            uint64_t mykeys;
            asset balance;
            name user;

            uint64_t primary_key() const { return user.value; }
        };

        TABLE Atable {
            name user;
            uint64_t scope;

            uint64_t primary_key() const { return scope; }

        };

        TABLE Btable {
            name user;
            uint64_t scope;

            uint64_t primary_key() const { return scope; }

        };

        typedef multi_index<"autokey12"_n, extra_autokey> inautokeys;
        typedef multi_index<"autokey23"_n, extra_autokey> outautokeys;
        typedef multi_index<"deleall1"_n, Atable> esall1;
        typedef multi_index<"deleall2"_n, Btable> esall2;

};
