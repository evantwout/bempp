%{
#include "assembly/assembly_options.hpp"


  %}


namespace Bempp
{

  %extend AssemblyOptions
  {
    %ignore switchToFmm;
    %ignore switchToOpenCl;
    %ignore swtichToTbb;
    %ignore parallelisationOptions;
  }
}

%include "assembly/assembly_options.hpp"





