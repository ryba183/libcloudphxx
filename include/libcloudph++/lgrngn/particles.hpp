#pragma once 

#include <libcloudph++/lgrngn/extincl.hpp>

#include "opts.hpp"
#include "output.hpp"
#include "opts_init.hpp"
#include "arrinfo.hpp"
#include "backend.hpp"

#include <mutex>
#include <condition_variable>

namespace libcloudphxx
{
  namespace lgrngn
  {
    // to allow storing instances for multiple backends in one container/pointer
    template <typename real_t>
    struct particles_proto_t 
    {
      // initialisation 
      virtual void init(
        const arrinfo_t<real_t> th,
        const arrinfo_t<real_t> rv,
        const arrinfo_t<real_t> rhod,
        const arrinfo_t<real_t> courant_x = arrinfo_t<real_t>(),
        const arrinfo_t<real_t> courant_y = arrinfo_t<real_t>(), 
        const arrinfo_t<real_t> courant_z = arrinfo_t<real_t>(),
        const std::map<enum chem_species_t, const arrinfo_t<real_t> > ambient_chem = std::map<enum chem_species_t, const arrinfo_t<real_t> >()
      ) { 
        assert(false);
      }  
 
      // stuff that requires Eulerian component to wait
      virtual void step_sync(
        const opts_t<real_t> &,
        arrinfo_t<real_t> th,
        arrinfo_t<real_t> rv,
        const arrinfo_t<real_t> rhod      = arrinfo_t<real_t>(),
        const arrinfo_t<real_t> courant_x = arrinfo_t<real_t>(),
        const arrinfo_t<real_t> courant_y = arrinfo_t<real_t>(),
        const arrinfo_t<real_t> courant_z = arrinfo_t<real_t>(),
        std::map<enum chem_species_t, arrinfo_t<real_t> > ambient_chem = std::map<enum chem_species_t, arrinfo_t<real_t> >()
      ) { 
        assert(false); 
      }  

      // returns accumulated rainfall
      virtual void step_async(
        const opts_t<real_t> &
      ) { 
        assert(false); 
      }  

      // method for accessing super-droplet statistics
      virtual void diag_sd_conc()                                   { assert(false); }
      virtual void diag_RH()                                   { assert(false); }
      virtual void diag_all()                                       { assert(false); }
      virtual void diag_rw_ge_rc()                                  { assert(false); }
      virtual void diag_RH_ge_Sc()                                  { assert(false); }
      virtual void diag_dry_rng(const real_t&, const real_t&)       { assert(false); }
      virtual void diag_wet_rng(const real_t&, const real_t&)       { assert(false); }
      virtual void diag_dry_mom(const int&)                         { assert(false); }
      virtual void diag_wet_mom(const int&)                         { assert(false); }
      virtual void diag_wet_mass_dens(const real_t&, const real_t&) { assert(false); }
      virtual void diag_chem(const enum chem_species_t&)            { assert(false); }
      virtual void diag_precip_rate()                               { assert(false); }
      virtual void diag_kappa_mom(const int&)                       { assert(false); }
      virtual void diag_kappa_rng(const real_t&, const real_t&)     { assert(false); }
      virtual void diag_max_rw()                                    { assert(false); }
      virtual void diag_vel_div()                                   { assert(false); }
      virtual std::map<output_t, real_t> diag_puddle()              { assert(false); }
      virtual real_t *outbuf()                                      { assert(false); return NULL; }

      // storing a pointer to opts_init (e.g. for interrogatin about
      // dimensions in Python bindings)
      opts_init_t<real_t> *opts_init;

      // virtual destructor
      virtual ~particles_proto_t() {};

    };  

    // prototype of what's implemented in the .tpp file
    template <typename real_t, backend_t backend>
    struct particles_t: particles_proto_t<real_t>
    {
      // initialisation 
      void init(
        const arrinfo_t<real_t> th,
        const arrinfo_t<real_t> rv,
        const arrinfo_t<real_t> rhod,
        const arrinfo_t<real_t> courant_x,
        const arrinfo_t<real_t> courant_y, 
        const arrinfo_t<real_t> courant_z,
        const std::map<enum chem_species_t, const arrinfo_t<real_t> > ambient_chem
      );

      // time-stepping methods
      void step_sync(
        const opts_t<real_t> &,
        arrinfo_t<real_t> th,
        arrinfo_t<real_t> rv,
        const arrinfo_t<real_t> rhod,
        const arrinfo_t<real_t> courant_x,
        const arrinfo_t<real_t> courant_y,
        const arrinfo_t<real_t> courant_z,
        std::map<enum chem_species_t, arrinfo_t<real_t> > ambient_chem
      );

      void step_async(
        const opts_t<real_t> &
      );

      // diagnostic methods
      void diag_sd_conc();
      void diag_RH();
      void diag_dry_rng(
        const real_t &r_mi, const real_t &r_mx
      );
      void diag_wet_rng(
        const real_t &r_mi, const real_t &r_mx
      );
      void diag_kappa_rng(
        const real_t &r_mi, const real_t &r_mx
      );
      void diag_dry_mom(const int &k);
      void diag_wet_mom(const int &k);
      void diag_kappa_mom(const int &k);
      void diag_wet_mass_dens(const real_t&, const real_t&);

      void diag_chem(const enum chem_species_t&);
      void diag_rw_ge_rc();
      void diag_RH_ge_Sc();
      void diag_all();
      void diag_precip_rate();
      void diag_kappa(const int&);
      void diag_max_rw();
      void diag_vel_div();
      std::map<output_t, real_t> diag_puddle();
      real_t *outbuf();

      struct impl;
      std::unique_ptr<impl> pimpl;

      // constructor
      particles_t(const opts_init_t<real_t> &opts_init, const int &n_x_bfr, int n_x_tot = 0); // n_x_bfr should have default=0, but python bindings fail if more than one default value...

      // declare destructor to delay it's definition until impl is defined
      ~particles_t();

      // helper typedef
      typedef particles_proto_t<real_t> parent_t;
    };



#if defined(__NVCC__)



    // specialization for the multi_GPU backend
    // has the init, stepping and diag functions
    // plus list of pointers to particles_t<CUDA> on each GPU
    // TODO: more elegant way?
    template <typename real_t>
    struct particles_t<real_t, multi_CUDA>: particles_proto_t<real_t>
    {
      // additional members
      // TODO: move these to impl
      std::vector<std::unique_ptr<particles_t<real_t, CUDA> > > particles; // pointer to particles_t on each GPU
      opts_init_t<real_t> glob_opts_init; // global copy of opts_init (threads store their own in impl), 
      const int n_cell_tot;               // total number of cells
      std::vector<real_t> real_n_cell_tot; // vector of the size of the total number of cells to store output

      // initialisation 
      void init(
        const arrinfo_t<real_t> th,
        const arrinfo_t<real_t> rv,
        const arrinfo_t<real_t> rhod,
        const arrinfo_t<real_t> courant_x = arrinfo_t<real_t>(),
        const arrinfo_t<real_t> courant_y = arrinfo_t<real_t>(), 
        const arrinfo_t<real_t> courant_z = arrinfo_t<real_t>(),
        const std::map<enum chem_species_t, const arrinfo_t<real_t> > ambient_chem = std::map<enum chem_species_t, const arrinfo_t<real_t> >()
      );

      // time-stepping methods
      void step_sync(
        const opts_t<real_t> &,
        arrinfo_t<real_t> th,
        arrinfo_t<real_t> rv,
        const arrinfo_t<real_t> rhod      = arrinfo_t<real_t>(),
        const arrinfo_t<real_t> courant_x = arrinfo_t<real_t>(),
        const arrinfo_t<real_t> courant_y = arrinfo_t<real_t>(),
        const arrinfo_t<real_t> courant_z = arrinfo_t<real_t>(),
        std::map<enum chem_species_t, arrinfo_t<real_t> > ambient_chem = std::map<enum chem_species_t, arrinfo_t<real_t> >()
      );
      void step_async(
        const opts_t<real_t> &
      );

      // diagnostic methods
      void diag_sd_conc();
      void diag_RH();
      void diag_dry_rng(
        const real_t &r_mi, const real_t &r_mx
      );
      void diag_wet_rng(
        const real_t &r_mi, const real_t &r_mx
      );
      void diag_dry_mom(const int &k);
      void diag_wet_mom(const int &k);
      void diag_wet_mass_dens(const real_t&, const real_t&);
      real_t *outbuf();

      void diag_chem(const enum chem_species_t&);
      void diag_rw_ge_rc();
      void diag_RH_ge_Sc();
      void diag_all();
      void diag_precip_rate();
      void diag_max_rw();
      void diag_vel_div();
      std::map<output_t, real_t> diag_puddle();

      // cxx threads helper methods
      // TODO: move them to impl!
      template<typename F, typename ... Args>
      void mcuda_run(F&& fun, Args&& ... args);

      template<class barrier_t>
      void step_async_and_copy(
        const opts_t<real_t> &opts,
        const int dev_id,
        std::vector<cudaStream_t> &streams,
        std::vector<cudaEvent_t> &events,
        barrier_t &
      );

      // constructors
      particles_t(const opts_init_t<real_t> &opts_init);

      // dtor
      ~particles_t();

      // helper typedef
      typedef particles_proto_t<real_t> parent_t;
    };
#endif
  };
};
