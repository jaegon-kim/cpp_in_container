#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include "utility/dump.hpp"
using namespace std;
namespace p17_02 {

    bool compare(const int & a, const int & b) {
        return a < b;
    }

    int shecule_shortest_job_first(vector<int> & jobs) {
        sort(jobs.begin(), jobs.end());
        //dump_vec(jobs, true);

        int prev_latency = 0, latency_sum = 0;
        for(size_t i = 1; i < jobs.size(); i++) {
            prev_latency += jobs[i - 1];
            latency_sum += prev_latency;
        }
        return latency_sum;
    }

    int schedule(list<int> & jobs, int prev_job, int prev_latency, int latency_sum, list<int> & path) {

        if (!jobs.size()) {
            //dump_list(path, false);
            //cout << " " << latency_sum << endl;
            return latency_sum;
        }

        size_t len = jobs.size();
        int min = 0x7fffffff;
        for (size_t i = 0; i < len; i++) {
            int job = jobs.front();
            jobs.pop_front();
            path.push_back(job);

            int new_latency = prev_latency + prev_job;
            int new_latency_sum = latency_sum + new_latency;

            int r = schedule(jobs, job, new_latency, new_latency_sum, path);
            if (r < min) {
                min = r;
            }

            path.pop_back();
            jobs.push_back(job);
        }
        return min;
    }

    void test(const list<int> & jobs) {
        list<int> j2 = jobs;
        list<int> path;
        int min = schedule(j2, 0, 0, 0, path);
        cout << "Complete Search Result       : " <<  min << endl;

        vector<int> v(jobs.begin(), jobs.end());
 
        int min2 = shecule_shortest_job_first(v);
        cout << "SJF(Shortest Job First) Result: " << min2 << endl;
    }
}

void test_p17_02_min_latency() {
    PRINT_FUNC_NAME;
    //p17_02::test(list<int> {2, 5, 1, 3});
    p17_02::test(list<int> {2, 5, 1, 3});

}