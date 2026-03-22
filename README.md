# ft_irc - Internet Relay Chat Server

A C++ implementation of an IRC (Internet Relay Chat) server for the 42Cursus curriculum.

## Project Overview

This project implements a functional IRC server capable of handling multiple concurrent clients connected via TCP sockets. The server manages channels, supports various IRC commands, and implements the IRC protocol for real-time communication between users.

### Features

**Core IRC Server (`ircserv`)**
- Multi-client TCP server using `poll()` for asynchronous I/O
- Channel management and client handling
- Password-protected server access
- Support for standard IRC commands:
  - **Connection**: `PASS`, `NICK`, `USER`
  - **Channel Operations**: `JOIN`, `KICK`, `INVITE`, `TOPIC`, `MODE`
  - **Messaging**: `PRIVMSG`
  - **User Management**: Channel modes and user modes
- Proper handling of IRC numerical replies and error codes
- C++98 compliant implementation

**Bonus Features (`irc_bot`)**
- IRC bot client implementation
- Automated bot actions and responses
- Bot-specific command handling

## Project Structure

```
ft_irc/
├── Makefile                    # Build configuration
├── mandatory/                  # Core IRC server implementation
│   ├── main.cpp               # Server entry point
│   ├── Inc/                   # Header files
│   │   ├── Server.hpp         # Server class definition
│   │   ├── Client.hpp         # Client class definition
│   │   ├── Channel.hpp        # Channel class definition
│   │   └── numericalReplies.hpp # IRC protocol replies
│   ├── server/                # Server implementation
│   │   ├── Server.cpp
│   │   └── Server_helper.cpp
│   ├── client/                # Client implementation
│   │   └── Client.cpp
│   ├── channel/               # Channel implementation
│   │   └── Channel.cpp
│   └── commands/              # IRC command implementations
│       ├── Pass.cpp
│       ├── Nick.cpp
│       ├── User.cpp
│       ├── Join.cpp
│       ├── Kick.cpp
│       ├── Invite.cpp
│       ├── Privmsg.cpp
│       ├── Topic.cpp
│       └── mode/              # Mode command utilities
│           ├── mode.cpp
│           └── utils.cpp
└── bonus/                     # Bonus: IRC bot implementation
    ├── main.cpp
    ├── tools.cpp
    ├── bot/
    │   ├── botClient.cpp
    │   ├── botClient.hpp
    │   ├── botActions.cpp
    │   └── botActions.cpp
    └── Inc/
        └── bot.hpp
```

## Building the Project

### Prerequisites

- C++ compiler (C++98 compatible)
- Make
- POSIX-compliant system (Linux/macOS)

### Build Commands

**Build the IRC server:**
```bash
make
```

This creates the `ircserv` executable.

**Build the bonus IRC bot:**
```bash
make bonus
```

This creates the `irc_bot` executable.

**Clean build artifacts:**
```bash
make clean
```

## Usage

### Running the IRC Server

```bash
./ircserv <port> <password>
```

**Parameters:**
- `<port>`: TCP port number for the server to listen on
- `<password>`: Server password required for client authentication

**Example:**
```bash
./ircserv 6667 secret_password
```

### Connecting to the Server

You can connect to the server using any standard IRC client:

```bash
irc_client -h localhost -p 6667
```

Or using `netcat` for testing:
```bash
nc localhost 6667
```

## IRC Protocol Implementation

### Supported Commands

| Command | Description |
|---------|-------------|
| `PASS` | Server password authentication |
| `NICK` | Set or change nickname |
| `USER` | Register user information |
| `JOIN` | Join a channel |
| `PART` | Leave a channel |
| `PRIVMSG` | Send private messages |
| `KICK` | Remove user from channel |
| `INVITE` | Invite user to channel |
| `TOPIC` | View or set channel topic |
| `MODE` | Modify channel or user modes |

### Authentication Flow

1. Client connects via TCP
2. Client sends `PASS` command with server password
3. Client sends `NICK` command with desired nickname
4. Client sends `USER` command with user information
5. Server responds with welcome numerics upon successful authentication

## Technical Details

### Architecture

- **Connection Handling**: Uses `poll()` for efficient multiplexed I/O
- **Data Structures**: Maps for managing clients and channels
- **Protocol**: IRC RFC-compliant with numerical reply codes
- **Language Standard**: C++98 (no modern C++ features)

### Key Classes

- **`Server`**: Main server class managing connections and channels
- **`Client`**: Represents a connected IRC client
- **`Channel`**: Represents an IRC channel with members and modes

### Compilation Flags

```
-Wall -Wextra -Werror -std=c++98
```

Strict compiler warnings are enforced to ensure code quality.

## Testing

You can test the server using IRC clients such as:
- `irssi` - Terminal IRC client
- `WeeChat` - Advanced IRC client
- `Telnet` or `netcat` - For basic protocol testing

**Example test with netcat:**
```bash
# Terminal 1: Start server
./ircserv 6667 password

# Terminal 2: Connect and send commands
nc localhost 6667
PASS password
NICK testuser
USER user 0 * :Real Name
```

## Bonus Features

The bonus implementation includes an IRC bot (`irc_bot`) that can perform automated actions and interact with the server. Build and run with:

```bash
make bonus
./irc_bot [parameters]
```

## Notes

- The implementation follows the 42 school coding style (Norm)
- Memory management is handled correctly with proper cleanup
- The server handles multiple concurrent connections efficiently
- All code compiles without warnings or errors under strict compiler flags

---

For more information about IRC protocol, visit: https://tools.ietf.org/html/rfc1459
