import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class arrange_dir {
    static String[] extensions;//without point
    static File[] files;
    static String path;

    public static void main(String[] args){
        path = System.getProperty("user.dir");
        files = (new File(path)).listFiles();
        extensions = new String[files.length];
        //iterate through each file
        for(int i=0; i<files.length; i++){
            //get file name
            String charsInName_String = files[i].getName();
                //iterate through each character
                for(int i2=0; i2<charsInName_String.length(); i2++){
                    //set extensions
                    if(charsInName_String.toCharArray()[i2] == '.')
                        extensions[i] = charsInName_String.substring(i2+1);
                }
        }
        classify();
    }

    private static void classify(){
        //make dirs
        for(int i=0; i<extensions.length; i++){
            File Folder = new File("\\"+extensions[i]);
            if(!Folder.exists()){
                new File(path+"\\"+extensions[i]).mkdirs();
            }
        }
        for(int i=0; i<files.length; i++){
            try {
                Files.move(files[i].toPath(), Paths.get("/"+extensions[i]));
            } catch (IOException e) {
                System.out.println("Error moving");
            }
        }
    }
}
