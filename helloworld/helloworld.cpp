#include <eosiolib/eosio.hpp>

using namespace eosio;

 CONTRACT helloworld: public contract {
    public:
        using contract::contract;

        ACTION hi (name user){
            check(has_auth(user), "missing authority");

            
            //require_auth(user);

            //has_auth() -> true/false 반환

            print("hello, ", user);
        }

    private:

 };