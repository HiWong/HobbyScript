package hobbyscript.Interpreter;

import hobbyscript.ApplicationTest.CodeDialog;
import hobbyscript.ast.AstNode;
import hobbyscript.ast.NullStmt;
import hobbyscript.Eval.Env.BasicEnvironment;
import hobbyscript.Eval.Env.Environment;
import hobbyscript.Exception.ParseException;
import hobbyscript.Lexer.HobbyLexer;
import hobbyscript.Parser.ScriptParser;
import hobbyscript.Token.HobbyToken;
import hobbyscript.Utils.logger.Logger;

import java.io.FileNotFoundException;
import java.io.FileReader;

/**
 * Script解释器
 *
 * @author liufengkai
 * Created by liufengkai on 16/7/15.
 */
public class ScriptInterpreter {

    static void run(String fileName, ScriptParser parser, Environment env) throws ParseException, FileNotFoundException {

        HobbyLexer lexer;
        if (fileName.equals("")) {
            lexer = new HobbyLexer(new CodeDialog());
        } else if (!fileName.contains("/")) {
            lexer = new HobbyLexer(new FileReader("Test/" + fileName));
        } else {
            lexer = new HobbyLexer(new FileReader(fileName));
        }

        Logger.init("Interpreter");

//        PrintUtils.startPrint();

        while (lexer.peek(0) != HobbyToken.EOF) {
            AstNode node = parser.parse(lexer);

            System.out.print(node.toJson());
            if (!(node instanceof NullStmt)) {
                Object r = node.eval(env);
//                PrintUtils.printAstTree(node);
//                Logger.v(" => " + r);
//                PrintUtils.printAstTreeGraph(node);
            }
        }

//        PrintUtils.endPrint();
    }


    public static void main(String[] args) throws ParseException, FileNotFoundException {
        run("", new ScriptParser(), new BasicEnvironment());
    }
}
