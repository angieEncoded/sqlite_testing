# SQLite testing and reference

- I followed along with this video with some notable deviations
    - Using C++20 to have access to std::format which is very close to JS string interpolation
    - I put the database logic into a singleton class instead of having it in main()
    - I also created a singleton class to keep my create table statements all in one place
- There's quite a lot more queries for various reference items
- Some of the things I'm passing around likely aren't necessary in prod and I wouldn't do it in an app that would be actually used
- 