#ifndef CHANNEL_HPP
#define CHANNEL_HPP
#pragma once
#include <string>
#include "Client.hpp"
#include "Server.hpp"
#include <ctime>


class Channel {
    private:
        std::string Name;
        std::string Password;

        std::time_t                             _creationTime;
        int                                     _capacityLimit;
        uint                                    _membersCount;
        std::map<std::string, Client>           _members;
        std::string                             _modes;
        std::map<std::string, Client>           _Ops;
        
        bool                                    _i;
        bool                                    _t;
        bool                                    _k;
        bool                                    _l;
        
        
        const std::map<std::string, Client >&    GetMembers(void) const;
        const std::map<std::string, Client >&    GetOps(void) const;
        
        
        int                                     getCapacityLimit( void ) const;
        uint                                    getMembersCount( void ) const;
        
        bool                                    is_restrectedTopic( void ) const;
        bool                                    is_userLimited( void ) const;
        bool                                    is_inviteOnly( void ) const;
        bool                                    is_keyed( void ) const;
        
        
        void                                    setKey( const std::string &password ) ;
        void                                    addModes( const char &mode );
        void                                    rmMode(const char &mode );
        void                                    addOps( Client &newOp );
        void                                    rmOps( Client &newOp );
        
        void                                    triggerMode( const char flag , const char mode, const bool isMode, bool &toTrigger ) ;
        void                                    setCapacityLimit( const std::string  &num );
        void                                    incrementCount( void );
        void                                    decrementCount( void );
        
        typedef std::map<std::string, Client >::const_iterator    constmap_it;
        typedef std::map<std::string, Client >::iterator           map_it;
        
        public:
        
        Channel();
        Channel( const std::string name );
        ~Channel();
        
        bool                                     is_Op( const std::string &name ) const;
        bool                                     is_Member( const std::string &name ) const;
        
        std::string                              getModes( void ) const;
        std::time_t                              getTime( void )const;
        
        void                                    set_i( char flag );
        void                                    set_t( char flag );
        void                                    set_k( char flag,  const std::string &pass);
        bool                                    set_o( char flag , Client &op );
        void                                    set_l( char flag , const std::string &num);
        
        std::string                             args;
        std::string                             changedModes;
        void                                    broadcastReply(const std::string &reply);
        
        std::string& GetName(void);
        void SetName(std::string& name);
        std::string& GetPassword(void);
        
        // const bool getModes( void ) const;
        // const bool getModes( void ) const;
        //get username of ops
    };
    
    #endif