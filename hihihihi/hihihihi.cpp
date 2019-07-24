#include <eosio/eosio.hpp>

using namespace eosio;

CONTRACT hihihihi: public contract {
    public:
        using contract::contract;

        ACTION hi (name user) {
            check( has_auth(user), "no Account");
            print("hi, ", user);
        }

        ACTION findage(uint64_t age) {
            address_index addresses(get_self(), get_self().value);
            auto forSecondary = addresses.get_index<"byage"_n>();

            auto itr = forSecondary.require_find(age, "no age");

            print(itr->user, " ", itr->age);
        }

        ACTION insert(name user, uint64_t age) {
            require_auth(get_self());

            address_index forInsert(get_self(), get_self().value);
            auto itr = forInsert.find(user.value);

            check( itr == forInsert.end(), "already exists");

            forInsert.emplace(user, [&](auto& row){
                row.user = user;
                row.age = age;
            });
            print("Insert success, Welcome, ", user);
        }

        ACTION remove(name user) {
             require_auth(get_self());

             address_index forRemove(get_self(), get_self().value);
             auto itr = forRemove.require_find(user.value, "no Account!!");
             forRemove.erase(itr);
            
            print("See you Next Time");
        }

        ACTION eraseall() {
             require_auth(user);

             address_index forErase(get_self(), get_self().value);
             auto itr = forErase.find(user.value);
             forErase.erase(itr);
            
            print("Erease All Compelete");
        }

        ACTION countuser (name user) {
            require_auth(user);
            address_index forCountuser(get_self(), get_self().value);
            auto itr = forCountuser.find(user.value);

            if(itr == forCountuser.end()){
                forCountuser.emplace(user, [&] (auto& row){
                    row.user = user;
                    row.count = 1;
    
                });

            } else {
                forCountuser.modify(itr, user, [&] (auto& row){
                    row.count++;
                });
            }
            print("success");
        }

         ACTION findcount(uint64_t count) {

            counts forFindcount(get_self(), get_self().value);
            auto forCountfind = forFindcount.get_index<"by_count"_n>();

            auto itr = forSecondary.find(count);

            if(itr != forSecondary.end()) {
                print(itr->user, " ", itr->count);
            }else {
                print("No body has that count number");
            }

        }

    private:
        struct [[eosio::table]] allowance {
            name user;
            uint64_t age;
            uint64_t count;

            uint64_t primary_key() const {return user.value;}
            uint64_t by_age() const { return age; }

        };
    typedef multi_index<"allowance3"_n , allowance, 
    indexed_by<"byage"_n, const_mem_fun<allowance, uint64_t, &allowance::by_age>>> address_index;
};