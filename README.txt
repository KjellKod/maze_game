To compile and use the tests
--------------------------------
1. In repository root directory: mkdir build && cd build && cmake && make -j
2. Run tests with `./UnitTestRunner` or `make test` or `ctest -v` or `ctest -V`

Not necessary to read: Only if you want to know about my 
Code Choices and Improvements
----------------------------------------------------------
1) A 3rd party library was chosen for the xml parsing. It would have been relatively easy to implement delimeter "token-extractor" but I had heard about pugixml and similar easy to use xml-libs before and was curious on how to use it as well as thought it would decrease the workload. Why re-invent the wheel, right?

In retrospective I think I spent at least 30-40% in checking out and testing different xml-libs. 
--> Which is OK. Now I know that pugixml works great!



2) Path-Walking is using a Breadth-First Search approach. A repetative BFS search approach. It can probably be improved upon but I like the solution as it stands now.


3) Improvement
String compare was used which is slow, especially for huge paths. An improvement to this solution would be to map each string "ID" to a unique numerical identifier. As proof-of-concept of the algorithm I think the string compare is fin but this performance remark is well worth thinking of if the maze are to be used for larger scenarios.

4) Improvement
Reading the scenario and map.xml files could be done asynchronously for nicer feedback to the user either through a GUI or even just progress information such as 
// psuedo code
    auto future_to_find = asynch(read_scenario_file, path_to_scenario_file);
    auto future_map = asynch(parse_xml_file, path_to_map_file);

    cout  << "Parsing configuration files ";
   while(!future_to_find.isReady() || !future_map.isReady()) {
      cout << ".";
      ms_sleep(500);
  }

5) Improvement
For user experience it is probably nicer to have a delay between every visit to a location in the map. That way the user can feel and build up excitement as more items are found. As it is now it is too quick to finish this automatic game for any user anticipation of "what's behind the next corner"

6) Overengineered solution?
Maybe? But I had fun ;)




