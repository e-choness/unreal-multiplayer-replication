# Shadow Dungeon: Unreal Multiplayer Replication

Shadow Dungeon is a self-taught project focused on implementing Online Subsystem replication using Unreal Engine 5.

It leverages official Unreal documentation and _Multiplayer Game Development with Unreal Engine 5_ by Marco Secchi.

[![show-case](./README-imgs/show-case.gif)](#requirements)

## Requirements

- [Unreal Engine 5.3.2](https://forums.unrealengine.com/t/5-3-2-hotfix-released/1370927) - Download via Epic Launcher.

## Features

- **Multiplayer Framework**: Includes replication for player actions, health, and interactions.
- **Enhanced Input System**: Supports modern input handling for movement, sprinting, and interaction.
- **AI Minions**: Patrol, chase, and interact with players dynamically.
- **Projectile System**: Fully replicated projectile mechanics with damage handling.
- **Custom Game Modes**: Includes Top-Down, Third-Person, and Multiplayer modes.
- **Animated 3D Assets**: Integration with Kay Lousberg's game assets and Megascans Vegetables.

## Epic Marketplace and External Asset Packages

- [Vehicle Variety Pack](https://www.unrealengine.com/marketplace/en-US/product/bbcb90a03f844edbb20c8b89ee16ea32)
- [Megascans - Vegetables](https://www.unrealengine.com/marketplace/en-US/product/8ef1598076964207bd38e14cf950f706)
- [Kay Lousberg's Game Assets](https://kaylousberg.com/)

## Getting Started

### Setup Instructions

1. Clone the repository

   ```bash
   git clone https://github.com/e-choness/shadow-dungeon.git
   ```

2. Running the Game

   - **Single Player**: Launch the game directly from the editor.
   - **Multiplayer**: Use the `MultiplayerGameMode` to host and join sessions.

3. Useful Tutorial Resources

   - [Unreal Network Fundamentals](https://youtu.be/09yWANtKmC8) - Covers replication basics.
   - [Multiplayer Best Practices](https://youtu.be/UstLLZbkmOQ) - Tips for optimizing multiplayer games.

## Project Structure

### Key Directories

- **Source/**: Contains all C++ code for gameplay mechanics, AI, and replication.
- **Content/**: Includes assets such as Blueprints, textures, and meshes.
- **Config/**: Configuration files for engine and project settings.

### Notable Files

- `PrototypeCharacter.h`: Defines the main player character.
- `SDMinion.h`: Handles AI minion behavior.
- `ThirdPersonProjectile.h`: Implements projectile mechanics.

## Credits

- [Multiplayer Game Development with Unreal Engine 5](https://github.com/PacktPublishing/Multiplayer-Game-Development-with-Unreal-Engine-5) by Marco Secchi.
- Unreal Engine Documentation and Tutorials.

## Contributing

Contributions are welcome! Please submit a pull request or open an issue for suggestions.

## License

This project is licensed under the [MIT License](LICENSE)
