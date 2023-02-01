#include <pybind11/pybind11.h>
#include "./mapf/include/cbs.hpp"
#include "./mapf/include/default_params.hpp"
#include "./mapf/include/ecbs.hpp"
#include "./mapf/include/hca.hpp"
#include "./mapf/include/icbs.hpp"
#include <iostream>
#include "./mapf/include/ir.hpp"
#include "./mapf/include/pibt.hpp"
#include "./mapf/include/pibt_complete.hpp"
#include "./mapf/include/problem.hpp"
#include "./mapf/include/push_and_swap.hpp"
#include <random>
#include "./mapf/include/revisit_pp.hpp"
#include <vector>
#include "./mapf/include/whca.hpp"
#include "./mapf/include/winpibt.hpp"

std::unique_ptr<Solver> getSolver(const std::string solver_name, Problem *P);

void process_mapf_problem_instance(std::string instance_file, std::string solver_name,
                                   std::string output_file,
                                   bool random_starts_goals = false)
{
  Problem P = Problem(instance_file);
  auto solver = getSolver(solver_name, &P);
  solver->solve();

  if (solver->succeed() && !solver->getSolution().validate(&P))
  {
    std::cout << "error@app: invalid results" << std::endl;
    return;
  }

  solver->printResult();
  solver->makeLog(output_file);
  std::cout << "save result as " << output_file << std::endl;
}

std::unique_ptr<Solver> getSolver(const std::string solver_name, Problem *P)
{
  std::unique_ptr<Solver> solver;
  if (solver_name == "PIBT")
  {
    solver = std::make_unique<PIBT>(P);
  }
  else if (solver_name == "winPIBT")
  {
    solver = std::make_unique<winPIBT>(P);
  }
  else if (solver_name == "HCA")
  {
    solver = std::make_unique<HCA>(P);
  }
  else if (solver_name == "WHCA")
  {
    solver = std::make_unique<WHCA>(P);
  }
  else if (solver_name == "CBS")
  {
    solver = std::make_unique<CBS>(P);
  }
  else if (solver_name == "ICBS")
  {
    solver = std::make_unique<ICBS>(P);
  }
  else if (solver_name == "PIBT_COMPLETE")
  {
    solver = std::make_unique<PIBT_COMPLETE>(P);
  }
  else if (solver_name == "ECBS")
  {
    solver = std::make_unique<ECBS>(P);
  }
  else if (solver_name == "RevisitPP")
  {
    solver = std::make_unique<RevisitPP>(P);
  }
  else if (solver_name == "PushAndSwap")
  {
    solver = std::make_unique<PushAndSwap>(P);
  }
  else if (solver_name == "IR")
  {
    solver = std::make_unique<IR>(P);
  }
  else if (solver_name == "IR_SINGLE_PATHS")
  {
    solver = std::make_unique<IR_SINGLE_PATHS>(P);
  }
  else if (solver_name == "IR_FIX_AT_GOALS")
  {
    solver = std::make_unique<IR_FIX_AT_GOALS>(P);
  }
  else if (solver_name == "IR_FOCUS_GOALS")
  {
    solver = std::make_unique<IR_FOCUS_GOALS>(P);
  }
  else if (solver_name == "IR_MDD")
  {
    solver = std::make_unique<IR_MDD>(P);
  }
  else if (solver_name == "IR_BOTTLENECK")
  {
    solver = std::make_unique<IR_BOTTLENECK>(P);
  }
  else if (solver_name == "IR_HYBRID")
  {
    solver = std::make_unique<IR_HYBRID>(P);
  }
  else
  {
    std::cout << "Unknown solver name, " + solver_name + ", continue with PIBT"
              << std::endl;
    solver = std::make_unique<PIBT>(P);
  }
  solver->setVerbose(true);
  return solver;
}

PYBIND11_MODULE(pymapf, pymapf_handle)
{
  pymapf_handle.doc() = "MAPF - Multi-Agent Path Finding module with Python bindings";
  pymapf_handle.def("process_mapf_problem_instance", &process_mapf_problem_instance);
}