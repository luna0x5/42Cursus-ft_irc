#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>
#include "Server.hpp"
#include "../client/Client.hpp"

class Channel {
    private:
        std::string Name;
        std::string Password;

        int                                     _capacityLimit;
        uint                                    _membersCount;
        std::map<std::string, Client>           _members;
        std::string                             _modes;
        std::map<std::string, Client>           _Ops;

        bool                                    _restrectedTopic;
        bool                                    _userLimited;
        bool                                    _inviteOnly;
        bool                                    _keyed;
        
        const std::map<std::string, Client >&   GetMembers(void) const;
        const std::map<std::string, Client >&   GetOps(void) const;

        const int                               getCapacityLimit( void ) const;
        const uint                              getCount( void ) const;
        const std::string                       getModes( void ) const;

        const bool                              is_Op( const std::string name ) const;
        const bool                              is_restrectedTopic( void ) const;
        const bool                              is_userLimited( void ) const;
        const bool                              is_inviteOnly( void ) const;
        const bool                              is_keyed( void ) const;


        void                                    addModes( const std::string mode );
        void                                    addOps( const Client &newOp);

        void                                    setKey( const std::string password ) ;
        void                                    setCapacityLimit( int num );

        void                                    triggeruserLimited( void ) ;
        void                                    triggerinviteOnly( void ) ;

        void                                    incrementCount( void );
        void                                    decrementCount( void );

    public:
        Channel();
        Channel(const std::string name);
        ~Channel();
    
        std::string& GetName(void);
        void SetName(std::string& name);
        std::string& GetPassword(void);
        void SetPassword(std::string& password);
        void SitBoolPswd(bool is);


    
        // const bool getModes( void ) const;
        // const bool getModes( void ) const;
        //get username of ops
};

#endif