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

        std::time_t                              _creationTime;
        size_t                                   _capacityLimit;
        uint                                     _membersCount;
        std::map<int, Client*>                  _members;
        std::string                             _modes;
        std::map<int, Client*>                  _Ops;
        
        bool                                    _i;
        bool                                    _t;
        bool                                    _k;
        bool                                    _l;
        
        
        const std::map<int, Client *>&    GetOps(void) const;
        
        
        
        
        void                                    setKey( const std::string &password ) ;
        void                                    addModes( const char &mode );
        void                                    rmMode(const char &mode );
        
        void                                    triggerMode( const char flag , const char mode, const bool isMode, bool &toTrigger ) ;
        void                                    setCapacityLimit( const std::string  &num );
        void                                    incrementCount( void );
        void                                    decrementCount( void );
        
        std::string topic;
        std::vector<std::string> invitedUsers;        
        
		public:
        typedef std::map<int, Client *>::const_iterator    constmap_it;
        typedef std::map<int, Client *>::iterator           map_it;
        void                                    rmOps( Client *newOp );
        
        Channel();
        Channel( const std::string name );
        ~Channel();
        
        uint                                    getMembersCount( void ) const;
        const std::map<int, Client *>&    GetMembers(void) const;
        bool                                     is_Op( int fd ) const;
        int                                      getCapacityLimit( void ) const;
        bool                                     is_Member( const std::string &name ) const;
        bool                                     is_keyed( void )const;
        bool                                     is_userLimited( void ) const;
        
        void                                     addMember(Client *client);
        void                                     rmMember(Client *client);
        void                                     addOps( Client *newOp );
        
        std::string                              getModes( void ) const;
        
        void                                    set_i( char flag );
        std::time_t                              getTime( void )const;
        void                                    set_t( char flag );
        void                                    set_k( char flag,  const std::string &pass);
        bool                                    set_o( char flag , Client *op );
        void                                    set_l( char flag , const std::string &num);
        bool                                    is_restrectedTopic( void ) const;
        bool                                    is_inviteOnly( void ) const;
        
        std::string                             args;
        std::string                             changedModes;
        bool                                    brdcast;
        void                                    broadcastReply(const std::string &reply);
        const std::string                       displayInfo(const std::string &nick);

        std::string& GetName(void);
        void SetName(std::string& name);
        std::string& GetPassword(void);
        
		const std::string getTopic() const;
	    void setTopic(const std::string& top);
		bool hasTopic() const;
		void addInvite(const std::string &nick);                
		bool isInvited(const std::string &nick) const;
		void removeInvite(const std::string &nick);
		void removeMember(const std::string &nick);

    };
    
    #endif