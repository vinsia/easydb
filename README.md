# easydb
This DB follow the design from the LevelDB

## Design

This db will be a key-value store. The key will be a string and the value will be a string.

Only support the key-based search, do not provide any index mechanism.
### Requirement

#### Interface
```C
std::string Get(std::string)

bool Put(std::string, str::string)
```

### Implementation

#### SkipList
class SkipList {
  private:
    Node* head_;
    const int kMaxHeight;
}

Find:
FindGreaterOrEqual(std::string_view key, Node** prev)
