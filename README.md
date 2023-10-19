# ImageProcessing_BlurFilter

Upon application launch, users are presented with a menu of options, accessible by selecting the corresponding number.
To ensure the application's extensibility and maintainability, the Model-View-Controller (MVC) design pattern is employed. 
The Model handles the core business logic, such as applying the blur filter, while the View manages user interactions and information display.
The Controller acts as the intermediary between the Model and View, forwarding user input to the Model for processing. 
In alignment with SOLID principles, the "FileOperations" class is introduced to centralize file-related operations, including existence checks,
validity assessments, and file name retrieval. This structured approach enhances code organization and facilitates future enhancements

When selecting the "Apply blur filter" option, the program meticulously guides the user through the process. It initially requests the complete TGA file path, 
followed by the user-specified blur factor within the range of 0.0 to 1.0, and the destination folder. To ensure a smooth operation, the program currently supports
paths in quotes, aligning with Windows' "Copy as Path" convention. A stringent validation process ensures that the user provides valid input for all options 
(TGA file, Blur factor, Destination folder) before proceeding. For now, I am supporting 24 and 32 bit, uncompressed true-color image (Image type -2).
Once user input is validated, the program engages the TGAFileOperation class for reading and writing TGA files. This class, which inherits from FileOperations, 
provides a foundation for future extensibility by allowing the addition of new file format support with minimal effort. The data read from the file is then passed
 to the Model, which processes the information and applies the blur filter using the ApplyBoxBlurFilter function. Following the filter application, the TGAFileOperation
class generates the new blurred image at the specified location. The name of the blurred image follows a naming convention: "Blur_OriginalImageName," with "Blur_" as the prefix. 
In the case of name conflicts, the program appends a numerical suffix to ensure each output file has a unique name. Throughout this process, the CLI interface
 provides detailed information, distinguishing between errors and instructions using distinct prefixes like “[ERROR]->” for error and “-->” for instruction.
Additionally, a Log class records application progress, errors, and warnings in a text file, which is defined by the programmer in the main function and located alongside the executable. 
This dual output system enhances user guidance and provides valuable insights for programmers tracking application behaviour.
