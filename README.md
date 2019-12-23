# transparency


[![CircleCI](https://circleci.com/gh/yourgithubhandle/transparency/tree/master.svg?style=svg)](https://circleci.com/gh/yourgithubhandle/transparency/tree/master)


**Contains the following libraries and executables:**

```
transparency@0.0.0
│
├─test/
│   name:    TestTransparency.exe
│   main:    TestTransparency
│   require: transparency.lib
│
├─library/
│   library name: transparency.lib
│   namespace:    Transparency
│   require:
│
└─executable/
    name:    TransparencyApp.exe
    main:    TransparencyApp
    require: transparency.lib
```

## Developing:

```
npm install -g esy
git clone <this-repo>
esy install
esy build
```

## Running Binary:

After building the project, you can run the main binary that is produced.

```
esy x TransparencyApp.exe 
```

## Running Tests:

```
# Runs the "test" command in `package.json`.
esy test
```
