#include <eosio/eosio.hpp>

using namespace eosio;

CONTRACT hihihihi: public contract {
    public:
        using contract::contract;

        ACTION hi (name user) {
            check( has_auth(user), "no Account");
            print("hi, ", user);
        }

        ACTION insert(name user) {
            require_auth(get_self());

            address_index forInsert(get_self(), get_self().value);
            auto itr = forInsert.find(user.value);

            check( itr == forInsert.end(), "already exists");

            forInsert.emplace(user, [&](auto& row){
                row.user = user;
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

    private:
        struct [[eosio::table]] allowance {
            name user;

            uint64_t primary_key() const {return user.value;}

        };
    typedef multi_index<"allowance"_n , allowance> address_index;
};