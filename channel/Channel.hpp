#ifndef CHANNEL_HPP
#define CHANNEL_HPP
#pragma once
#include <string>
#include "../client/Client.hpp"
#include "../server/Server.hpp"
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
        
        
        
        
        int                                     getCapacityLimit( void ) const;
        uint                                    getMembersCount( void ) const;
        
        bool                                    is_restrectedTopic( void ) const;
        bool                                    is_userLimited( void ) const;
        bool                                    is_inviteOnly( void ) const;
        
        
        void                                    setKey( const std::string &password ) ;
        void                                    addModes( const char &mode );
        void                                    rmMode(const char &mode );
        void                                    rmOps( Client &newOp );
        
        void                                    triggerMode( const char flag , const char mode, const bool isMode, bool &toTrigger ) ;
        void                                    setCapacityLimit( const std::string  &num );
        void                                    incrementCount( void );
        void                                    decrementCount( void );
        
        typedef std::map<std::string, Client >::const_iterator    constmap_it;
        typedef std::map<std::string, Client >::iterator           map_it;
        
		std::string topic;
		std::vector<std::string> invitedUsers;
        public:
        
        Channel();
        Channel( const std::string name );
        ~Channel();
        
        bool                                    is_keyed( void ) const;
        const std::map<std::string, Client >&    GetMembers(void) const;
        const std::map<std::string, Client >&    GetOps(void) const;
        bool                                     is_Op( const std::string &name ) const;
        bool                                     is_Member( const std::string &name ) const;
        
        void                                     addMember(Client &client);
        void                                     addOps( Client &newOp );
        
        std::string                              getModes( void ) const;
        std::time_t                              getTime( void )const;
        
        void                                    set_i( char flag );
        void                                    set_t( char flag );
        void                                    set_k( char flag,  const std::string &pass);
        bool                                    set_o( char flag , Client &op );
        void                                    set_l( char flag , const std::string &num);
        
		bool	get_t(void) { return(_t); } //TODO: IMPLEMENT IN DIFFERNT FILE
		bool	get_i(void) { return(_i); } //TODO: IMPLEMENT IN DIFFERNT FILE

        std::string                             args;
        std::string                             changedModes;
        void                                    broadcastReply(const std::string &reply);
        
        std::string& GetName(void);
        void SetName(std::string& name);
        std::string& GetPassword(void);
        
		//TODO: TO PUT THE DEFINITION IN DIFFERENT FILE
		const std::string& getTopic() const { return topic; }
	    void setTopic(const std::string& top) { topic = top; }
		bool hasTopic() const { return !topic.empty(); }
		void addInvite(const std::string &nick)
		{
			// Avoid duplicates
			if (!isInvited(nick))
				invitedUsers.push_back(nick);
		}

		bool isInvited(const std::string &nick) const
		{
			for (size_t i = 0; i < invitedUsers.size(); ++i)
			{
				if (invitedUsers[i] == nick)
					return true;
			}
			return false;
		}

		void removeInvite(const std::string &nick)
		{
			for (std::vector<std::string>::iterator it = invitedUsers.begin();
				it != invitedUsers.end(); ++it)
			{
				if (*it == nick)
				{
					invitedUsers.erase(it);
					return;
				}
			}
		}
		void removeMember(const std::string &nick)
		{
			std::map<std::string, Client>::iterator it = _members.find(nick);
			if (it != _members.end())
			{
				_members.erase(it);
				if (_membersCount > 0)
					_membersCount--;
			}

			// If the user was also an operator, remove them from _Ops
			std::map<std::string, Client>::iterator opIt = _Ops.find(nick);
			if (opIt != _Ops.end())
				_Ops.erase(opIt);
		}

        // const bool getModes( void ) const;
        // const bool getModes( void ) const;
        //get username of ops
    };
    
    #endif