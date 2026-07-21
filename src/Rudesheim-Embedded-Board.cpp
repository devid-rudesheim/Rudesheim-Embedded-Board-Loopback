#include "Rudesheim-Embedded-Board.hpp"

#include <map>
#include <stdexcept>

namespace Rudesheim::Embedded
{
  namespace Option
  {
    namespace
    {
      class Loopback:
        virtual public Signal
      {
        mutable std::map< uint8_t, float >
          values;

      public:
        virtual auto Write( Location const &location, float value ) const -> void override
        {
          values[ location.Number() ] = value;
        }

        virtual auto Read( Location const &location ) const -> float override
        {
          auto const
            found = values.find( location.Number() );

          return found == values.end() ? 0.0f : found->second;
        }

        auto Clear() const -> void
        {
          values.clear();
        }
      };

      struct Digital:
        virtual public Loopback
      {
        virtual auto Resolution() const -> uint8_t override
        {
          return 1;
        }
      };

      struct Analog8Bit:
        virtual public Loopback
      {
        virtual auto Resolution() const -> uint8_t override
        {
          return 8;
        }
      };

      struct Analog12Bit:
        virtual public Loopback
      {
        virtual auto Resolution() const -> uint8_t override
        {
          return 12;
        }
      };

      struct Default:
        virtual public Mode
      {
        virtual auto ConfigureInput( Location const & ) const -> void override
        {
        }

        virtual auto ConfigureOutput( Location const & ) const -> void override
        {
        }
      };

      struct PullUp:
        virtual public Mode
      {
        virtual auto ConfigureInput( Location const & ) const -> void override
        {
        }

        virtual auto ConfigureOutput( Location const & ) const -> void override
        {
          throw std::logic_error( "PullUp is not valid for Output pins" );
        }
      };

      struct On:
        virtual public Steady
      {
        virtual auto Name() const -> char const* override
        {
          return "ON";
        }

        virtual auto Level() const -> float override
        {
          return 1.0f;
        }
      };

      struct Off:
        virtual public Steady
      {
        virtual auto Name() const -> char const* override
        {
          return "OFF";
        }

        virtual auto Level() const -> float override
        {
          return 0.0f;
        }
      };
    }
  }

  Board const
    &board = Class< TestBoard >::SoleObject();

  TestBoard const
    &test_board = Class< TestBoard >::SoleObject();

  auto TestBoard::DigitalSignal() const -> Option::Signal const &
  {
    return Class< Option::Digital >::SoleObject();
  }

  auto TestBoard::Analog8BitSignal() const -> Option::Signal const &
  {
    return Class< Option::Analog8Bit >::SoleObject();
  }

  auto TestBoard::Analog12BitSignal() const -> Option::Signal const &
  {
    return Class< Option::Analog12Bit >::SoleObject();
  }

  auto TestBoard::DefaultMode() const -> Option::Mode const &
  {
    return Class< Option::Default >::SoleObject();
  }

  auto TestBoard::PullUpMode() const -> Option::Mode const &
  {
    return Class< Option::PullUp >::SoleObject();
  }

  auto TestBoard::SteadyOn() const -> Option::Steady const &
  {
    return Class< Option::On >::SoleObject();
  }

  auto TestBoard::SteadyOff() const -> Option::Steady const &
  {
    return Class< Option::Off >::SoleObject();
  }

  auto TestBoard::Reset() const -> void
  {
    Class< Option::Digital >::SoleObject().Clear();
    Class< Option::Analog8Bit >::SoleObject().Clear();
    Class< Option::Analog12Bit >::SoleObject().Clear();
  }
}
