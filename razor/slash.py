import getopt, sys, os

from . import utils

from . import passes

def main():
    utils.setLogger()
    Slash(sys.argv).run()
    return 0

class Slash(object):
    
    def __init__(self, argv):
        (flags, args) = getopt.getopt(argv[1:], None, ['work-dir='])
        self.manifest = utils.get_manifest(args)
        if self.manifest is None:
            self.usage(argv[0])
            self.ok = False
            return
        self.work_dir = utils.get_work_dir(flags)
        self.ok = True
        
    def  usage(self, exe):
        sys.stderr.write('{0} [--work-dir=<dir>] <manifest>\n'.format(exe))


    def run(self):
        
        if not self.ok: return

        if not utils.make_work_dir(self.work_dir): return

        (ok, module, binary, libs, args, name) = utils.check_manifest(self.manifest)

        #<delete this once done>
        new_libs = []
        for lib in libs:
            new_libs.append(os.path.realpath(lib))
                            
        libs = new_libs
        #</delete this once done>


        if not ok: return

        files = utils.populate_work_dir(module, libs, self.work_dir)

        os.chdir(self.work_dir)

        #specialize the arguments ...
        if not (args is None):
            main = files[module]
            pre = main.get()
            post = main.new('a')
            passes.specialize_program_args(pre, post, args, 'arguments', name=name)
            
        
        
