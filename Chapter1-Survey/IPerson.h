#pragma once
// IPerson.h

namespace Elementary {

  struct IPerson {
    using Name = std::string;
    using Occupation = std::string;
    using Age = int;
    using Stats = std::tuple<Name, Occupation, Age>;

    virtual Stats stats() const = 0;
    virtual void stats(const Stats& sts) = 0;
    virtual Name name() const = 0;
    virtual Occupation occupation() const = 0;
    virtual void occupation(const Occupation& occup) = 0;
    virtual Age age() const = 0;
    virtual void age(const Age& ag) = 0;
  };
}
