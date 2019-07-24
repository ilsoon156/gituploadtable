#include <eosio/eosio.hpp>

using namespace eosio;

CONTRACT countfun: public contract {

    public:
        using contract::contract;

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

        ACTION eraseall() {
             require_auth(get_self());

            counts forEraseAll(get_self(), get_self().value);
            auto itr = forEraseAll.begin();

            while(itr != forEraseAll.end()) {
                itr = froEraseAll.erase(itr);
            
            }
            print("Erease All Compelete");
            
        }




    private:
    struct [[eosio::table]] counttable {
            name user;
            uint64_t count;

            uint64_t primary_key() const {return user.value;}
            uint64_t by_count() const { return count; }

        };
    typedef multi_index<"counttalbe"_n , counttable, 
    indexed_by<"bycount"_n, const_mem_fun<counttable, uint64_t, &counttable::by_count>>> address_index;

};