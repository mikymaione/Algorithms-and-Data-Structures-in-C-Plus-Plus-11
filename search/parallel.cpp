/*
MIT License

Copyright (c) 2023 Michele Maione

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <random>
#include <thread>
#include "parallel.h"

std::vector<std::string_view> parallel::split(std::string_view str, const char delim) {
    std::vector<std::string_view> result;

    auto left = str.begin();

    for (auto it = left; it != str.end(); ++it) {
        if (*it == delim) {
            result.emplace_back(&*left, it - left);
            left = it + 1;
        }
    }

    if (left != str.end())
        result.emplace_back(&*left, str.end() - left);

    return result;
}

void parallel::find_occurrence_in_vector(const std::vector<std::string_view> &content, const std::string &word,
                                         const size_t from, const size_t to) {
    for (auto x = from; x < to; x++)
        if (content[x] == word)
            occurrence += 1;
}

void parallel::run() {
    const auto content =
            "A powerful fox known as the Nine-Tails attacks Konoha, the hidden leaf village in the Land of Fire, one of the Five Great Shinobi Countries in the Ninja World. In response, the leader of Konoha and the Fourth Hokage, Minato Namikaze, at the cost of his life, seals the fox inside the body of his newborn son, Naruto Uzumaki, making him a host of the beast.[i] The Third Hokage returns from retirement to become the leader of Konoha again. Naruto is often scorned by Konoha's villagers for being the host of the Nine-Tails. Due to a decree by the Third Hokage forbidding any mention of these events, Naruto learns nothing about the Nine-Tails until 12 years later, when Mizuki, a renegade ninja, reveals the truth to him. Naruto defeats Mizuki in combat, earning the respect of his teacher, Iruka Umino.[ii] Shortly afterward, Naruto becomes a ninja and joins with Sasuke Uchiha, against whom he often competes, and Sakura Haruno, on whom he has a crush, to form Team 7, under an experienced sensei, the elite ninja Kakashi Hatake. Like all the ninja teams from every village, Team 7 completes missions requested by the villagers, ranging from doing chores and being bodyguards to performing assassinations. After several missions, including a major one in the Land of Waves, Kakashi allows Team 7 to take a ninja exam, enabling them to advance to a higher rank and take on more difficult missions, known as Chunin Exams. During the exams, Orochimaru, a wanted criminal, invades Konoha and kills the Third Hokage for revenge. Jiraiya, one of the three legendary ninjas, declines the title of Fifth Hokage and searches with Naruto for Tsunade whom he chooses to become Fifth Hokage instead. During the search, it is revealed that Orochimaru wishes to train Sasuke because of his powerful genetic heritage, the Sharingan.[iii] After Sasuke attempts and fails to kill his older brother Itachi,[iv] who had showed up in Konoha to kidnap Naruto, he joins Orochimaru, hoping to gain from him the strength needed to kill Itachi. The story takes a turn when Sasuke leaves the village: Tsunade sends a group of ninja, including Naruto, to retrieve Sasuke, but Naruto is unable to persuade or force him to come back. Naruto and Sakura do not give up on Sasuke; Naruto leaves Konoha to receive training from Jiraiya to prepare himself for the next time he encounters Sasuke, while Sakura becomes Tsunade's apprentice.";

    const auto t = std::make_unique<parallel>();

    const auto occurrence = t->find_occurrence(content, ' ', "Naruto");
    std::cout << "Occurrence: " << occurrence << std::endl;
}

int parallel::find_occurrence(const std::string &content, const char delim, const std::string &word) {
    // may return 0 when not able to detect
    const auto processor_count = std::thread::hardware_concurrency();
    const auto processor_to_use = std::max(processor_count, 1u);

    const auto words = split(content, delim);

    const auto words_count_d = static_cast<double>(words.size());
    const auto processor_to_use_d = static_cast<double>(processor_to_use);

    const auto words_for_processor_precise = words_count_d / processor_to_use_d;
    const auto words_for_processor = static_cast<size_t>(std::ceil(words_for_processor_precise));

    occurrence = 0;

    std::vector<std::thread> threads;

    for (size_t x = 0; x < processor_to_use; x++) {
        const auto next = x == 0 ? 0 : 1;
        const auto from = x * words_for_processor + next;
        const auto to = std::min((x + 1) * words_for_processor, words.size());

        threads.emplace_back(
            &parallel::find_occurrence_in_vector, this, words, word, from, to
        );
    }

    std::ranges::for_each(
        threads,
        std::mem_fn(&std::thread::join)
    );

    return occurrence;
}
