// vim:filetype=cpp
/** @file
  * @copyright University of Warsaw
  * @section LICENSE
  * GPLv3+ (see the COPYING file or http://www.gnu.org/licenses/)
  */

namespace libcloudphxx
{
  namespace lgrngn
  {
    namespace detail
    {
      template <typename real_t>
      struct nextafter_to_zero
      {
        real_t from;

        nextafter_to_zero(real_t from) : from(from) {}

        BOOST_GPU_ENABLED
        real_t operator()(real_t x)
        {
          return x < from ? x : nextafter(x, real_t(0.));
        }
      };
    };

    template <typename real_t, backend_t device>
    void particles_t<real_t, device>::impl::unpack_n(const int &n_copied)
    {
      n_part_old = n_part;
      n_part += n_copied;

      if(n_copied==0)
        return;

      assert(opts_init.n_sd_max >= n_part);
      n.resize(n_part);
      thrust::copy(in_n_bfr.begin(), in_n_bfr.begin() + n_copied, n.begin() + n_part_old);
    }

    template <typename real_t, backend_t device>
    void particles_t<real_t, device>::impl::unpack_real(const int &n_copied)
    {
      if(n_copied==0)
        return;

      auto it = distmem_real_vctrs.begin();

      while (it != distmem_real_vctrs.end())
      {
        (*it)->resize(n_part);
        auto distance = std::distance(distmem_real_vctrs.begin(), it);
        thrust::copy( in_real_bfr.begin() + distance * n_copied, in_real_bfr.begin() + (distance+1) * n_copied, (*it)->begin() + n_part_old);
        it++;
      }

      // in single precision, bcnd_remote_lft (and potentially rgt) sometimes gives x=x1. we clean this up here
      thrust::transform(x.begin() + n_part_old, x.end(), x.begin() + n_part_old, detail::nextafter_to_zero<real_t>(opts_init.x1));

#if !defined(NDEBUG)
      auto min_it = thrust::min_element(x.begin() + n_part_old, x.end());
      if(*min_it < opts_init.x0)
      {
        std::cerr << "x (" << *min_it << ")  < opts_init.x0 (" << opts_init.x0 << ") after unpacking, potentially SD moved by more than one process/GPU domain size" << std::endl;
        assert(0);
      }
      auto max_it = thrust::max_element(x.begin() + n_part_old, x.end());
      if(*max_it >= opts_init.x1)
      {
        std::cerr << "x (" << *max_it << ")  >= opts_init.x1 (" << opts_init.x1 << ") after unpacking, potentially SD moved by more than one process/GPU domain size" << std::endl;
        assert(0);
      }
#endif
    }

    template <typename real_t, backend_t device>
    void particles_t<real_t, device>::impl::flag_lft()
    {
      thrust::copy(
        thrust::make_constant_iterator<n_t>(0),
        thrust::make_constant_iterator<n_t>(0) + lft_count,
        thrust::make_permutation_iterator(n.begin(), lft_id.begin())
      );
    }

    template <typename real_t, backend_t device>
    void particles_t<real_t, device>::impl::flag_rgt()
    {
      thrust::copy(
        thrust::make_constant_iterator<n_t>(0),
        thrust::make_constant_iterator<n_t>(0) + rgt_count,
        thrust::make_permutation_iterator(n.begin(), rgt_id.begin())
      );
    }
  };
};

