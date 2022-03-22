# ECS
ECS (entity component system) implementation testing in C++.

# Environment
- C++ 14

# Example
## Creating an Entitie and Adding Components
```C++
auto entity = scene.createEntity();
scene.addComponent<TransformComponent>(entity);
scene.addComponent<MaterialComponent>(entity);
```

## Adding a System
```C++
auto meshRenderer = std::make_unique<MeshRenderer>();
scene.addSystem(std::move(meshRenderer));
```


# Reference
- https://savas.ca/nomad
- https://cowboyprogramming.com/2007/01/05/evolve-your-heirachy/
- https://zenn.dev/rita0222/articles/c22a8367e31b4d5f4eeb
