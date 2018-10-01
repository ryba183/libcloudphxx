// vim:filetype=cpp
/** @file
  * @copyright University of Warsaw
  * @section LICENSE
  * GPLv3+ (see the COPYING file or http://www.gnu.org/licenses/)
  */

#include <libcloudph++/common/turbulence.hpp>

namespace libcloudphxx
{
  namespace lgrngn
  {
    namespace detail
    {
      struct common__turbulence__tau_relax
      {
        template<class real_t>
        BOOST_GPU_ENABLED
        real_t operator()(const real_t &wet_mom_1, const real_t &dv)
        {
          return common::turbulence::tau_relax(wet_mom_1 / dv / si::square_metres) / si::seconds;
        }
      };

      template<class real_t>
      struct common__turbulence__turb_dot_ss
      {
        template<class tpl_t>
        BOOST_GPU_ENABLED
        real_t operator()(tpl_t tpl)
        {
          return common::turbulence::dot_turb_ss(
            quantity<si::dimensionless, real_t>(thrust::get<0>(tpl)),
            thrust::get<1>(tpl) * si::metres / si::seconds,
            thrust::get<2>(tpl) * si::seconds
          ) * si::seconds;
        }
      };
    };

    // calc the SGS turbulent supersaturation
    template <typename real_t, backend_t device>
    void particles_t<real_t, device>::impl::hskpng_turb_dot_ss()
    {   
      // calc tau_relax
      moms_calc(rw2.begin(), real_t(1./2), false);
      thrust_device::vector<real_t> &tau_rlx(count_mom); 
      thrust::transform(
        tau_rlx.begin(),
        tau_rlx.end(),
        dv.begin(),
        tau_rlx.begin(),
        detail::common__turbulence__tau_relax()
      );

      // calc ss perturb for each SD
      thrust::transform(
        thrust::make_zip_iterator(thrust::make_tuple(
          ssp.begin(),
          wp.begin(),
          thrust::make_permutation_iterator(tau_rlx.begin(), ijk.begin())
        )),
        thrust::make_zip_iterator(thrust::make_tuple(
          ssp.begin(),
          wp.begin(),
          thrust::make_permutation_iterator(tau_rlx.begin(), ijk.begin())
        )) + n_part,
        dot_ssp.begin(),
        detail::common__turbulence__turb_dot_ss<real_t>()
      );
    }
  };
};
