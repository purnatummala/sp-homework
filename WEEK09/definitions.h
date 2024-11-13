#ifndef __DEFINITIONS__H__
#define __DEFINITIONS__H__

#include <functional>
#include <string>
#include <map>
#include <chrono>
#include <iostream>
#include <unordered_map>
#include <cmath> // Include cmath for std::abs

// Base Function class
class Function
{
protected:
    mutable unsigned int count{0};
    bool uses_cache{false};

public:
    virtual double operator()(double x) const = 0;
    virtual ~Function() = default;
    unsigned int getCount() const
    {
        return count;
    }
    void resetCounter() const { count = 0; }
    virtual void clearCache() const {}
    bool isCacheEnabled() const { return uses_cache; }
    double evaluate(double x) const
    {
        count++; // Increment counter for every evaluation
        return operator()(x);
    }
};

// Original CachedFunction class with O(log N) lookup
class CachedFunction : public Function
{
private:
    std::function<double(double)> f;
    mutable std::map<double, double> cache; // Ordered map
    mutable int evaluationCount = 0;
    double tol;

    bool hasNearbyValue(double x, double &result) const
    {
        for (const auto &pair : cache)
        {
            if (std::abs(pair.first - x) < tol)
            {
                result = pair.second;
                return true;
            }
        }
        return false;
    }

public:
    CachedFunction(std::function<double(double)> func, double tol = 1e-7)
        : f(func), cache(), tol(tol)
    {
        uses_cache = true;
    }

    double operator()(double x) const override
    {
        double result;
        if (hasNearbyValue(x, result))
        {
            return result;
        }
        evaluationCount++;
        result = f(x);
        cache[x] = result;
        return result;
    }

    void clearCache() const override
    {
        cache.clear();
    }

    int getEvaluationCount() const
    {
        return evaluationCount;
    }

    void resetEvaluationCount() const
    {
        evaluationCount = 0;
    }
};

// FastCachedFunction class with O(1) lookup
class FastCachedFunction : public Function
{
private:
    std::function<double(double)> f;
    mutable std::unordered_map<int, double> cache; // Integer key for binning
    double tol;

    // Convert double to bin number
    int getBin(double x) const
    {
        return static_cast<int>(std::round(x / tol));
    }

public:
    FastCachedFunction(std::function<double(double)> func, double tol = 1e-7)
        : f(func), cache(), tol(tol)
    {
        uses_cache = true;
    }

    double operator()(double x) const override
    {
        int bin = getBin(x);
        auto it = cache.find(bin);
        if (it != cache.end())
        {
            return it->second;
        }
        count++;
        double result = f(x);
        cache[bin] = result;
        return result;
    }

    void clearCache() const override
    {
        std::cout << "Cache being cleared! Was size=" << cache.size() << "\n";
        cache.clear();
    }

    void resetEvaluationCount() const
    {
        count = 0;
    }
};

#endif
