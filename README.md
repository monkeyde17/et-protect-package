cocos-console plugins -- xxhash
===============================

## Introduce 

the xxhash plugins is based on `cocos-console`

the plugins is just hash the `pro.android/bin/classes.dex` file,
and write the hash value to `Resources/config.et`.

## Config

I think you can success use `cocos` to build Android package. The command as follow:

```bash
cocos compile -p android -m realase
```

### add xxhash plugins

`cocos-console-dir` ：`cocos2dx-3.0-ROOT/tools/cocos2d-console/`

```bash
cp -r console/* cocos-console-dir/plugins/
echo plugin_xxhash.CCPluginHash >> cocos-console-dir/bin/cocos2d.in
```

-----------

you can test the plugin in terminal. The command as follow:

[xxhash](./console/)

```bash
cocos xxhash -p android -m release
```

> PS : the `debug` mode is different of `release` mode.

### cpp

add all file as follow into your project.

```bash
ETProtectData.h
ETProtect.h
ETProtect.cpp
```

> PS : the default seed is 0x12345678

### java

add some code into AppActivity.java


```java
public class AppActivity extends Cocos2dxActivity {
        
    public static String getPath() {
        return getContext().getPackageCodePath();
    }
}
```

> PS : if you are add the static method `getPath()` in other Java file, you need modify `JniHelper` argument in the `ETProtect.cpp`

## useage

you can use as follow:

```cpp
if (ETProtect::isOriginPackage()) {
    /* do something */
} else {
    /* do something */
}
```

## TODOLIST

- [ ] add the `so` files' value
- [ ] add config shell, like `config.sh`

