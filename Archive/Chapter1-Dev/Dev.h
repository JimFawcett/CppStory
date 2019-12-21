#pragma once
// Dev.h

#include "IDev.h"
#include "../Chapter1-Person/Person.h"

namespace Elementary {

  class Dev : public Person, public IDev {
  public:
    //using Projects = std::vector<std::string>;
    //using Education = std::string;
    //using Office = std::string;
    //using DevStats = std::tuple<Stats, Education, Office, Projects>;

    Dev();
    Dev(const DevStats& dstats);
    ~Dev();
    virtual Projects projects() const override;
    virtual void projects(const Projects& prjs);
    virtual Education education() const override;
    virtual Office office() const override;
    virtual void devStats(const DevStats& sstats);
    virtual DevStats devStats() const override;
    virtual void meeting();
    virtual void work();

    //-------------------------------------------------
    // From IPerson
    //-------------------------------------------------
    //virtual Stats stats() const = 0;
    //virtual void stats(const Stats& sts) = 0;
    //virtual Name name() const = 0;
    //virtual Age age() const = 0;
    //virtual void age(const Age& ag) = 0;
    // From Person
    //virtual Stats stats() const override;
    //virtual void stats(const Stats& sts) override;
    //virtual bool isValid() const override;
    //virtual Name name() const override;
    //virtual Occupation occupation() const override;
    //virtual void occupation(const Occupation& occup) override;
    //virtual Age age() const override;
    //virtual void age(const Age& ag) override;

  private:
    DevStats devStats_;
  };

  //inline std::unique_ptr<IDev> createDev();
}