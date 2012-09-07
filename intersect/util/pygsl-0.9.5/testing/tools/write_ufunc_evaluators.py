"""
"""
import sys
import string
from cStringIO import StringIO



class UFuncType:
    """
    
    """
    def __init__(self):
        self.type = None
        self.fake_type = None

    def SetType(self, type):
        self.type = type

    def SetFake(self, type):
        self.fake_type = type

    def GetCast(self):
        pass

    def IsResulte10(self):
        if self.type == 'erf' or self.type == 'erd':
            return 1
        return 0

    def IsResult(self):
        if self.type == 'rf' or self.type == 'rd':
            return 1
        return 0
    
    def __GetType(self, type, argumentnumber):
        t = type
        if t == 'f':
            return "float"

        if t == 'd':
            return "double"

        if t == 'i':
            return "int"

        if t == 'ui':
            return "unsigned int"

        if t == 'rd':
            return "double"


        if t == 'erd':
            if argumentnumber == 2:
                return "int"
            return "double"
        
        if t == 'erf':
            if argumentnumber == 2:
                return "int"
            return "float"

        if t == 'rf':
            return "float"

        if t == 'm':
            return "gsl_mode_t"
        
        raise ValueError, "Unknown Type %s " % self.type
        
    def GetFakeType(self, argumentnumber):
        if self.fake_type:
            return self.__GetType(self.fake_type, argumentnumber)
        return None
    
    def GetType(self, argumentnumber):
        return self.__GetType(self.type, argumentnumber)
    
    def GetNArgs(self):
        if self.type == 'rf' or self.type == 'rd':            
            return 2
        if self.type == 'erf' or self.type == 'erd':
            return 3
        return 1
        
        
class UFuncWriter:
    _namecheck = "PyGSL_sf_ufunc_"
    _namecheck_l = len(_namecheck)
    _prototype = "(char **args, int *dimensions, int *steps, void *func)"
    
    def __init__(self, line):
        self.description = None
        self.funccast = None
        self.in_types = []
        self.out_types = []
        self.error_check = None
        self.__faker = 0
        
        description = string.split(line, ':')[0]        
        assert(description[:self._namecheck_l] == self._namecheck)
        self.description = description
        
        description = description[self._namecheck_l:]
        self.__definetypes(description)

        
    def __definetypes(self, description):
        # Is this type a fakeing one ?
        argument_types = string.split(description, "_as_")
        #print argument_types,
        
        arguments = None
        fakes = None
        if len(argument_types) == 1:
            self.__faker = 0
            arguments = argument_types[0]
        elif len(argument_types) == 2:
            arguments = argument_types[0]
            fakes =argument_types[1]
            self.__faker = 1
        else:
            raise ValueError, "More than one as in Type string!"

        if fakes:
            self.funccast = self._namecheck + fakes            
        else:
            self.funccast = self._namecheck + arguments
        # Split the in from the out args:
        #print arguments,
        in_types, out_types = string.split(arguments, "_")
        #print in_types, out_types
        in_fake_types, out_fake_types = None, None
        if fakes:
            in_fake_types, out_fake_types = string.split(fakes, "_")
            assert(len(in_types) == len(in_fake_types))
            assert(len(out_types) == len(out_fake_types))

            
        self.__add_types(self.in_types, in_types, in_fake_types)
        self.__add_types(self.out_types, out_types, out_fake_types)
        # Iterate over the real types.
        #print "ins", self.in_types
        #print "outs", self.out_types
        #print
        
    def __add_types(self, list, arguments, fakes):
        i = 0
        while i < len(arguments):
            tmp = UFuncType()
            #multi letter descriptions
            typedescr_end = i + 1
            t = arguments[i]
            if t == 'r' or t == 'u':
                typedescr_end  = i + 2
            if t == 'e':
                typedescr_end  = i + 3
            descr = arguments[i:typedescr_end]
            tmp.SetType(descr)
            if fakes:
                test = fakes[i:typedescr_end]
                if test != descr:
                    tmp.SetFake(test)                
            list.append(tmp)
            i = typedescr_end


    def add_in_types(self):
        counter = 0
        for i in self.in_types:
            for j in range(i.GetNArgs()):
                if counter > 0:
                    print ",",
                test = 0    
                try:
                    fake = i.GetFakeType(j)
                    if fake:
                        print "(%s)*((%s *)ip%d)" % (fake, i.GetType(j), counter),
                    else:
                        print "*((%s *)ip%d)" % (i.GetType(j),counter),
                    test = 1
                finally:
                    if test == 0:
                        sys.stderr.write("self.funccast = %s\n" % self.funccast)
                counter += 1
        return counter        
        
    def function_call_with_flag(self):
        print "\t\t{"
        print "\t\tint flag;"
        counter = 0

        # need temporary variables
        for i in self.out_types:
            if i.IsResult():
                print "\t\tgsl_sf_result r%d;" % counter
            elif i.IsResulte10():
                print "\t\tgsl_sf_result_e10 r%d;" % counter
            elif i.GetFakeType(0):
                print "%s tmp%d;" % (i.GetFakeType(0), counter)                
            counter += 1;
            
        print "\t\tflag = ((%s *) func)(" % (self.funccast),

        # function call
        if self.add_in_types():
            print ",",
            
        counter = 0
        out_counter = 0
        for i in self.out_types:
            if counter > 0:
                print ",",
            test = 0    
            try:
                if i.IsResult():
                    print "r%d" % counter,
                    counter += 1
                elif i.IsResulte10():
                    print "r%d" % counter,
                    counter += 1
                elif i.GetFakeType(0):
                    print "tmp%d" % counter,
                    counter += 1
                else:    
                    print "(%s *)op%d" % (i.GetType(0), out_counter),
                test = 1
            finally:
                if test == 0:
                    sys.stderr.write("self.funccast = %s\n" % self.funccast)
            out_counter += 1
        print ")"
        print "\t\tif (flag != GSL_SUCCESS){"
        out_counter = 0;
        for i in self.out_types:
            for j in range(i.GetNArgs()):
                print "\t\t\t*(%s) op%d = (%s) gsl_nan()" %(i.GetType(j), out_counter, i.GetType(j))
                out_counter += 1
        print "\t\t\treturn;"
        print "\t\t}"
        # readout
        counter = 0
        out_counter = 0
        for i in self.out_types:
            test = 0    
            try:
                if i.IsResult() or i.IsResulte10():
                    if i.GetFakeType(0):
                        print "\t\t*(%s) op%d = (%s) r%d.val;" % (i.GetType(0), out_counter, i.GetType(0),  counter)
                        print "\t\t*(%s) op%d = (%s) r%d.err;" % (i.GetType(1), out_counter+1,i.GetType(1),  counter)
                    else:
                        print "\t\t*(%s) op%d = r%d.val;" % (i.GetType(0), out_counter, counter)
                        print "\t\t*(%s) op%d = r%d.err;" % (i.GetType(1), out_counter+1, counter)                        
                    counter += 1
                    out_counter +=2
                    if i.IsResulte10():
                        print "\t\t*(int) op%d = r%d.e10;" % (out_counter, counter)
                        out_counter +=1
                elif i.GetFakeType(0):
                    print "\t\t(%s) op%d = (%s) tmp%d" %(i.GetType(0), out_counter,  i.GetType(0), counter),
                    counter += 1
                    out_counter += 1

                test = 1
            finally:
                if test == 0:
                    sys.stderr.write("self.funccast = %s\n" % self.funccast)
            out_counter += 1        
        print "\t\t}"


    def function_call_without_flag(self):
        fake = self.out_types[0].GetFakeType(0)
        if fake:
            print "\t\t*(%s *)op0 = (%s)((%s *) func)(" % (fake, self.out_types[0].GetType(0), self.funccast),
        else:
            print "\t\t*(%s *)op0 = ((%s *) func)(" % (self.out_types[0].GetType(0), self.funccast),
        self.add_in_types()
        print ");"
    
    def __call__(self):
        stream = StringIO()
        save = sys.stdout
        sys.stdout = stream
        counter = 0
        in_counter = 0
        out_counter = 0
        try:            
            print "void %s (char **args, int *dimensions, int *steps, void *func){" % self.description
            print "\tint i, ",
            for i in self.in_types:
                for j in range(i.GetNArgs()):
                    if counter > 0:
                        print ",",
                    print "is%d=steps[%d]" % (in_counter,counter),
                    counter += 1
                    in_counter +=1
            for i in self.out_types:
                for j in range(i.GetNArgs()):
                    if counter > 0:
                        print ",",
                    print "os%d=steps[%d]" % (out_counter,counter),
                    counter += 1
                    out_counter +=1
            print ";"        

            counter = 0
            in_counter = 0
            out_counter = 0
        
            print "\tchar  ",
            for i in self.in_types:
                for j in range(i.GetNArgs()):
                    if counter > 0:
                        print ",",
                    print "*ip%d=args[%d]" % (in_counter,counter),
                    counter += 1
                    in_counter +=1
                    
            for i in self.out_types:
                for j in range(i.GetNArgs()):
                    if counter > 0:
                        print ",",
                    print "*op%d=args[%d]" % (out_counter,counter),
                    counter += 1
                    out_counter +=1
            print ";"     

            print "\tfor(i = 0; i<dimensions[0]; i++){"
            
            counter = 0
            in_counter = 0
            out_counter = 0

            for i in self.in_types:
                for j in range(i.GetNArgs()):
                    print "\t\tip%d+=is%d;" % (in_counter,in_counter)
                    counter += 1
                    in_counter +=1
                    
            for i in self.out_types:
                for j in range(i.GetNArgs()):
                    print "\t\top%d+=os%d;" % (out_counter,out_counter)
                    counter += 1
                    out_counter +=1

            #print "x = (float*)ip1;"
            #print "mode = (int *) ip2;"
            funccast =  self.funccast
            use_error_flag = 0
            if 'r' in funccast or 'e' in funccast:
                use_error_flag = 1
                self.function_call_with_flag()
            else:
                test = 0
                if len(self.out_types) != 1:
                    sys.stderr.write("Not wrapping %s!\n" % funccast)
                else:
                    self.function_call_without_flag()
            print "\t}"        
                # uses gsl_sf_result or gsl_sf_result_e10_
            #print "flag = ((PyGSL_DOUBLE_FUNC_di_dd *)func)((double)*x, (gsl_mode_t) *mode, &result);"

            # Use some heuristics to guess the out type.

            #if (flag == GSL_SUCCESS){
            #    *(float *)op1 = (float)result.val;
            #    *(float *)op2 = (float)result.err;
            #    } else {             
            #    *(float *)op1 = (float)gsl_nan();
            #    *(float *)op2 = (float)gsl_nan();
            #    invoke_error_handler(__FILE__, __FUNCTION__, i, flag);
            #    }
            #}

            print "}"
            stream.seek(0)            
            return stream.read()        
        finally:
            sys.stdout = save
def run():
    file = open("sf__ufuncs.txt")
    out = open("sf_evals.c", "w")
    for line in file.readlines():        
        out.write(UFuncWriter(line)())
        
if __name__ == '__main__':
    run()

