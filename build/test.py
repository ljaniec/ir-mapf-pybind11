from pymapf import process_mapf_problem_instance

instance_file = "../instances/arena_300agents_1.txt"
solver_name = "PIBT"
output_file = "result.txt"
random_starts_goals = False
# void process_mapf_problem_instance(std::string instance_file, std::string solver_name,
#                                    std::string output_file,
#                                    bool random_starts_goals = false)
process_mapf_problem_instance(
    instance_file, solver_name, output_file, random_starts_goals
)
