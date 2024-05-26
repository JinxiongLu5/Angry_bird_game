// #include "httplib.h"
// #include "json.hpp"
// #include <fstream>
// #include <iostream>

// std::string scoreFilePath = "../media/scores/local_data.json";

// void mergeScores(const nlohmann::json& clientScores, const std::string& serverFilePath) {
//     nlohmann::json serverData;

//     // Load server scores from file
//     std::ifstream inputFile(serverFilePath);
//     if (inputFile.is_open()) {
//         inputFile >> serverData;
//         inputFile.close();
//     } else {
//         // If the server file does not exist, initialize it as an empty JSON object
//         serverData = nlohmann::json::object();
//     }

//     // Iterate through client scores and merge with server scores
//     for (const auto& [level, players] : clientScores.items()) {
//         for (const auto& [name, score] : players.items()) {
//             if (!serverData[level].contains(name) || serverData[level][name] < score) {
//                 serverData[level][name] = score;
//             }
//         }
//     }

//     // Write the merged data back to the server file
//     std::ofstream outputFile(serverFilePath);
//     if (outputFile.is_open()) {
//         outputFile << serverData.dump(4); // Pretty-print with an indent of 4 spaces
//         outputFile.close();
//     } else {
//         std::cerr << "Could not open " << serverFilePath << " for writing." << std::endl;
//     }
// }


// int main(void) {
//     using namespace httplib;
//     Server svr;

//     svr.Post("/upload_scores", [](const Request& req, Response& res) {
//         nlohmann::json clientScores = nlohmann::json::parse(req.body);
//         mergeScores(clientScores, scoreFilePath);
//         res.set_content("Scores uploaded successfully", "text/plain");
//     });

//     svr.Get("/retrieve_scores", [](const Request& req, Response& res) {
//         std::ifstream file(scoreFilePath);
//         if (file.is_open()) {
//             std::string scores((std::istreambuf_iterator<char>(file)),
//                                 std::istreambuf_iterator<char>());
//             file.close();
//             res.set_content(scores, "application/json");
//         } else {
//             res.status = 404;
//             res.set_content("Scores not found", "text/plain");
//         }
//     });

//     svr.listen("0.0.0.0", 1234);
// }
