/*
 * =====================================================================================
 * 
 *       Filename:  l_bfgs.h
 * 
 *    Description:  
 * 
 *        Version:  1.0
 *        Created:  03/04/2008 10:09:29 PM EST
 *       Revision:  none
 *       Compiler:  gcc
 * 
 *         Author:  Nikolaos Vasiloglou (NV), nvasil@ieee.org
 *        Company:  Georgia Tech Fastlab-ESP Lab
 * 
 * =====================================================================================
 */

#ifndef L_BFGS_H_
#define L_BFGS_H_

#include "fastlib/fastlib.h"
#include <string>

template<typename OptimizedFunction>
class LBfgs {
 public:
  void Init(OptimizedFunction *optimized_function, datanode* module);
  void Destruct();
  void ComputeLocalOptimumBFGS();
  void ReportProgress();
  void ReportProgressFile(std::string file);
  void GetResults(Matrix *result);
  void Reset(); 
  void set_coordinates(Matrix &coordinates);
  void set_desired_feasibility(double desired_feasibility);
  void set_feasibility_tolerance(double feasibility_tolerance);
  void set_norm_grad_tolerance(double norm_grad_tolerance);
  void set_max_iterations(index_t max_iterations);
  Matrix *coordinates();
  double sigma();
  void set_sigma(double sigma);

 private:
  void InitOptimization_();
  void ComputeWolfeStep_();
  void UpdateLagrangeMult_();
  success_t ComputeWolfeStep_(double *step, Matrix &direction);
  success_t ComputeBFGS_(double *step, Matrix &grad, index_t memory);
  success_t UpdateBFGS_();
  success_t UpdateBFGS_(index_t index_bfgs);
  void BoundConstrain();
  std::string ComputeProgress_();
  void ReportProgressFile_();

  struct datanode* module_;
  OptimizedFunction  *optimized_function_;
  index_t num_of_iterations_;
  index_t num_of_points_;
  index_t new_dimension_;
  double sigma_;
  double objective_factor_;
  double eta_;
  double gamma_;
  double step_;
  double desired_feasibility_;
  double feasibility_tolerance_;
  double norm_grad_tolerance_;
  double wolfe_sigma1_;
  double wolfe_sigma2_;
  double wolfe_beta_;
  double min_beta_;
  bool silent_;
  ArrayList<Matrix> s_bfgs_;
  ArrayList<Matrix> y_bfgs_;
  Vector ro_bfgs_;
  index_t index_bfgs_;
  Matrix coordinates_;
  Matrix previous_coordinates_;
  Matrix gradient_;
  Matrix previous_gradient_;
  index_t max_iterations_;
  double step_size_;
  // the memory of bfgs 
  index_t mem_bfgs_;
  FILE *fp_log_;
};

#include "l_bfgs_impl.h"
#endif //L_BFGS_H_
