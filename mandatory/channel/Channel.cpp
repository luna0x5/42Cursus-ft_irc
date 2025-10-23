#include "Channel.hpp"

Channel::Channel():Name("default") , _capacityLimit(0), _membersCount(0), _modes("+") ///
, _i(false), _t(false), _k(false), _l(false)
{
    this->_creationTime = std::time(NULL);
    // this->_members.clear();
    // this->_Ops.clear();
}

Channel::Channel( const std::string name ): Name(name), _capacityLimit(0), _membersCount(0), _modes("+")
, _i(false), _t(false), _k(false), _l(false)
{
    this->_creationTime = std::time(NULL);
    // this->_members.clear();
    // this->_Ops.clear();
}

Channel::~Channel(){}

const std::map<std::string, Client >&
Channel::GetMembers(void)const {
return this->_members;
}

const std::map<std::string, Client >&
Channel::GetOps(void)const {
    return this->_Ops;
}

int
Channel::getCapacityLimit( void ) const 
{
    return this->_capacityLimit;
}

uint
Channel::getMembersCount( void ) const 
{
    return this->_membersCount;
}

std::string
Channel::getModes( void ) const 
{
    return this->_modes;
}

bool
Channel::is_Op( const std::string &name ) const
{
    std::map<std::string, Client>::const_iterator it = this->_Ops.find(name);

    return (it != this->_Ops.end()) ? true : false;
}


bool
Channel::is_Member( const std::string &name ) const
{
    std::map<std::string, Client>::const_iterator it = this->_members.find(name);
    return (it != this->_members.end()) ? true : false;
}

bool
Channel::is_restrectedTopic( void )const
{
    return this->_t;
}

bool
Channel::is_userLimited( void )const
{
    return this->_l;
}
bool
Channel::is_inviteOnly( void )const
{
    return this->_i;
}
bool
Channel::is_keyed( void )const
{
    return this->_k;
}

void
Channel::addModes( const char &mode )
{
    this->_modes += mode;
}

void Channel::rmMode(const char &mode)
{
    std::string::size_type pos = this->_modes.find(mode);
    if (pos != std::string::npos) {
        this->_modes.erase(pos, 1); 
    }
}

void
Channel::addOps( Client &newOp )
{
    if (!is_Op(newOp.getnick()))
        this->_Ops[newOp.getnick()] = newOp;

}

void
Channel::rmOps( Client &newOp )
{
    if (is_Op(newOp.getnick()))
        this->_Ops.erase(newOp.getnick());

}

void
Channel::addMember(Client &client)
{
    if (!is_Member(client.getnick()))
        this->incrementCount();

    this->_members[client.getnick()] = client;
}

void
Channel::rmMember(Client &client)
{
    if (is_Member(client.getnick()))
        this->decrementCount();

    this->_members.erase(client.getnick());
}

void
Channel::setKey( const std::string &password )
{
    this->Password = password;
    this->args+=" " + password;
}

void
Channel::setCapacityLimit( const std::string &num )
{
    std::stringstream   extract(num);
    size_t                 i;

    if (extract >> i)
    {
        if (i > 0)
        {
            this->_capacityLimit = i;
            this->triggerMode('+', 'l', this->is_userLimited(), this->_l);
            this->args += " " + to_string(i);
        }

    }
        
}

void
Channel::set_i( char flag)
{
    triggerMode(flag, 'i', this->is_inviteOnly(), this->_i);
}

void
Channel::set_t( char flag)
{
    triggerMode(flag, 't', this->is_restrectedTopic(), this->_t);
}

void
Channel::set_k( char flag, const std::string &pass)
{
    if (this->is_keyed() && flag == '+')
        this->changedModes += "k";
    triggerMode(flag, 'k', this->is_keyed(), this->_k);
    if (flag == '+')
        this->setKey(pass);
    else
        this->setKey("*");
}

bool
Channel::set_o( char flag, Client &op )
{
    std::string name = op.getnick();
    constmap_it    oper = this->GetMembers().find(name);

    if (oper == this->GetMembers().end())
        return false;
    if (flag == '+')
        addOps(op);
    else
        rmOps(op);

    this->changedModes += "o";
    this->args += " " + name;
    return true;
}

void
Channel::set_l( char flag , const std::string &num )
{
    if (flag == '+')
        setCapacityLimit(num); 
    else
        this->triggerMode('-', 'l', this->is_userLimited(), this->_l);
}

void
Channel::triggerMode( const char flag , const char mode, const bool isMode, bool &toTrigger )
{
    if (flag == '+' && !isMode)
    {
        this->changedModes+= mode;
        this->addModes(mode);
        toTrigger = true;
    }
    else if (flag == '-' && isMode)
    {
        this->changedModes+= mode;
        this->rmMode(mode);
        toTrigger = false;
    }
}

void
Channel::incrementCount( void )
{
    this->_membersCount++;
}

void
Channel::decrementCount( void )
{
    this->_membersCount--;
}

std::string& Channel::GetName(void){return Name;}

void Channel::SetName(std::string& name){Name=name;}

std::string& Channel::GetPassword(void){
    return Password;
}

std::time_t
Channel::getTime( void )const
{
    return this->_creationTime;
}

// void
// Channel::broadcastReply(const std::string &reply)
// {
//TODO: there's a problem after this line == the message doesn't get broadcasted
//     if (this->changedModes.empty())
//         return ;

//     std::map<std::string, Client>   members = this->GetMembers();
//     constmap_it                     clients = members.begin();

//     for (; clients !=  members.end(); clients++)
//         Server::sendReply(clients->second.getFd(), reply);
//     std::cerr<<"sent => RPL_MODE."<<std::endl;
// }

void
Channel::broadcastReply(const std::string &reply)
{
    std::map<std::string, Client>   members = this->GetMembers();
    constmap_it                     clients = members.begin();

    for (; clients !=  members.end(); clients++)
        Server::sendReply(clients->second.getFd(), reply);
}

bool	Channel::get_t(void)
{
	return(_t);
}
bool	Channel::get_i(void)
{
	return(_i);
}

const std::string& Channel::getTopic() const
{
	return (topic);
}
void Channel::setTopic(const std::string& top)
{
	topic = top;
}
bool Channel::hasTopic() const
{
	return (!topic.empty());
}
void Channel::addInvite(const std::string &nick)
{
	// Avoid duplicates
	if (!isInvited(nick))
		invitedUsers.push_back(nick);
}
bool Channel::isInvited(const std::string &nick) const
{
	for (size_t i = 0; i < invitedUsers.size(); ++i)
	{
		if (invitedUsers[i] == nick)
			return true;
	}
	return false;
}

void Channel::removeMember(const std::string &nick)
{
	std::map<std::string, Client>::iterator it = _members.find(nick);
	if (it != _members.end())
	{
		_members.erase(it);
		if (_membersCount > 0)
			_membersCount--;
	}
}
