#pragma once

#include <unordered_set>

namespace hpp
{

// Allows bool functionality over several independent criteria
// If any criteria exist within the set - the type's value is true
// If no criteria exist - the type's value is false

template<typename Criterion>
class criteria
{
    using criterion_set_t = std::unordered_set<Criterion>;
    criterion_set_t set_ {};

public:

    // Returns true if no criteria exist
    auto empty() const -> bool
    {
        return set_.empty();
    }

    // Returns true if a specific criterion exists
    auto has( const Criterion& criterion ) const -> bool
    {
        return set_.find(criterion) != std::end(set_);
    }

    // Inserts a criterion
    auto emplace( const Criterion& criterion ) -> bool
    {
        const auto it = set_.find( criterion );
        if( it != std::end(set_) )
        {
            return false;
        }

        set_.emplace( criterion );
        return true;
    }

    // Inserts a criterion
    auto emplace( Criterion&& criterion ) -> bool
    {
        const auto it = set_.find( criterion );
        if( it != std::end(set_) )
        {
            return false;
        }

        set_.emplace( std::move(criterion) );
        return true;
    }

    // Inserts a criterion
    auto insert( const Criterion& criterion ) -> bool
    {
        return emplace( criterion );
    }

    // Removes a criterion
    auto erase( const Criterion& criterion ) -> bool
    {
        const auto it = set_.find( criterion );
        if( it == std::end(set_) )
        {
            return false;
        }

        set_.erase( it );
        return true;
    }

    // Returns true if any criterion exists
    bool operator==( bool check ) const
    {
        return (!empty() == check);
    }

    // Returns true if any criterion exists
    explicit operator bool() const
    {
        return !empty();
    }
};

} // namespace hpp
