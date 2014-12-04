//
//  GPDRegistrationViewController.m
//  GPShopper-iOS
//
//  Created by Matthew Reed on 10/28/14.
//  Copyright (c) 2014 James Lee. All rights reserved.
//

#import "GPDRegistrationViewController.h"

@interface GPDRegistrationViewController () <UITextFieldDelegate>
{
    SCRegistrationState *state;
    SCProfile *profile;
    SCSession *session;
}


@property (strong, nonatomic) IBOutlet UITextField *firstNameTextField;
@property (strong, nonatomic) IBOutlet UITextField *lastNameTextField;
@property (strong, nonatomic) IBOutlet UITextField *emailTextField;
@property (strong, nonatomic) IBOutlet UITextField *phoneTextField;
@property (strong, nonatomic) IBOutlet UITextField *passwordTextField;
@property (strong, nonatomic) IBOutlet UITextField *passwordConfirmationTextField;
@property (strong, nonatomic) IBOutlet UIBarButtonItem *previousButton;
@property (strong, nonatomic) IBOutlet UIBarButtonItem *nextButton;
@property (strong, nonatomic) IBOutlet UIBarButtonItem *doneButton;
@property (strong, nonatomic) IBOutlet UIToolbar *toolbar;
@property (strong, nonatomic) IBOutlet UIScrollView *scrollView;
@property (strong, nonatomic) UITextField *activeField;
@property (strong, nonatomic) IBOutlet UIActivityIndicatorView *spinner;

@end

@implementation GPDRegistrationViewController

@synthesize firstNameTextField;
@synthesize lastNameTextField;
@synthesize emailTextField;
@synthesize phoneTextField;
@synthesize passwordTextField;
@synthesize passwordConfirmationTextField;
@synthesize toolbar;
@synthesize scrollView;
@synthesize activeField;
@synthesize spinner;

- (instancetype)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        state = [SCRegistrationState defaultState];
        profile = [SCProfile defaultProfile];
        session = [[SCSession alloc] initWithRegState:state];
        [SCSession setRequestUrl:[NSBundle standardClientHostName]];
    }
    return self;
}


- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    firstNameTextField.inputAccessoryView = toolbar;
    lastNameTextField.inputAccessoryView = toolbar;
    emailTextField.inputAccessoryView = toolbar;
    phoneTextField.inputAccessoryView = toolbar;
    passwordTextField.inputAccessoryView = toolbar;
    passwordConfirmationTextField.inputAccessoryView = toolbar;
    
    firstNameTextField.delegate = self;
    lastNameTextField.delegate = self;
    emailTextField.delegate = self;
    phoneTextField.delegate = self;
    passwordTextField.delegate = self;
    passwordConfirmationTextField.delegate = self;
    
    [self registerForKeyboardNotifications];
    
    [state addObserver:self forKeyPath:@"status" options:0 context:nil];
    [profile addObserver:self forKeyPath:@"updateStatus" options:0 context:nil];
    NSNotificationCenter *center = [NSNotificationCenter defaultCenter];
    [center addObserverForName:@"scsession_updated" object:session queue:nil usingBlock:^(NSNotification *note) {
        if (session.exists) {
            [profile sendUpdates];
        } else if (session.createFailed) {
            
        } else if (session.destroyFailed) {
            
        }
        
    }];
}

- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self name:@"scsession_updated" object:session];
    @try {
        [state removeObserver:self forKeyPath:@"status"];
        [profile removeObserver:self forKeyPath:@"updateStatus"];
    }
    @catch (NSException *exception) {
        
    }
    
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}
- (IBAction)registerButtonPressed:(id)sender {
    NSRegularExpression *regex = [[NSRegularExpression alloc] initWithPattern:@"^[A-Z0-9a-z._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,4}$" options:(NSRegularExpressionCaseInsensitive) error:nil];
    NSTextCheckingResult *match = [regex firstMatchInString:emailTextField.text options:0 range:NSMakeRange(0, [emailTextField.text length])];
    
    if ([firstNameTextField.text  isEqual: @""] ||
        [lastNameTextField.text isEqual:@""] ||
        [emailTextField.text isEqual:@""] ||
        [phoneTextField.text isEqual:@""] ||
        [passwordTextField.text isEqual:@""] ||
        [passwordConfirmationTextField isEqual:@""]) {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Error"
                                                        message:@"You must enter all fields."
                                                       delegate:self
                                              cancelButtonTitle:@"OK"
                                              otherButtonTitles:nil, nil];
        [alert show];
    } else if (!match) {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Error"
                                                        message:@"Please enter a valid email."
                                                       delegate:self
                                              cancelButtonTitle:@"OK"
                                              otherButtonTitles:nil, nil];
        [alert show];
    } else if (![passwordTextField.text isEqual:passwordConfirmationTextField.text]) {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Error"
                                                        message:@"Passwords must match."
                                                       delegate:self
                                              cancelButtonTitle:@"OK"
                                              otherButtonTitles:nil, nil];
        [alert show];
    } else {
        [profile stageUpdatedFirstName:firstNameTextField.text];
        [profile stageUpdatedLastName:lastNameTextField.text];
        [profile stageUpdatedEmail:emailTextField.text];
        [profile stageSupplementalValue:phoneTextField.text forKey:@"phone"];
        [profile stageSupplementalValue:passwordTextField.text forKey:@"password"];
        [state loginWithIdentifier:emailTextField.text zipcode:@""];
        
    }
}

- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary *)change context:(void *)context {
    if ([keyPath isEqualToString:@"status"]) {
        switch (state.status) {
            case SCRegStatusUnregistered:
                
                break;
            case SCRegStatusBusy:
                
                break;
            case SCRegStatusFail:
                
                break;
            case SCRegStatusSuccess:
                [self registerAccount];
                break;
        }
    } else if ([keyPath isEqualToString:@"updateStatus"]) {
        switch (profile.updateStatus) {
            case SCProfileRemoteSuccess:
                [self createAccount];
                break;
            case SCProfileRemoteNone:
                break;
            case SCProfileRemoteFail:
                break;
            case SCProfileRemoteBusy:
                break;
        }
    }
}

- (void)registerAccount {
    [session create];
}

- (void)createAccount {
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"You have been registered" message:@"" delegate:self cancelButtonTitle:@"Ok" otherButtonTitles:nil, nil];
    [alert show];
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (IBAction)doneButtonPressed:(id)sender {
    [self.view endEditing:YES];
}

- (void)registerForKeyboardNotifications
{
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(keyboardWasShown:)
                                                 name:UIKeyboardDidShowNotification object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(keyboardWillBeHidden:)
                                                 name:UIKeyboardWillHideNotification object:nil];
    
}

- (void)keyboardWasShown:(NSNotification*)aNotification
{
    NSDictionary* info = [aNotification userInfo];
    CGSize kbSize = [[info objectForKey:UIKeyboardFrameBeginUserInfoKey] CGRectValue].size;
    
    UIEdgeInsets contentInsets = UIEdgeInsetsMake(64.0, 0.0, kbSize.height, 0.0);
    scrollView.contentInset = contentInsets;
    scrollView.scrollIndicatorInsets = contentInsets;
    
    // If active text field is hidden by keyboard, scroll it so it's visible
    // Your app might not need or want this behavior.
    CGRect aRect = self.view.frame;
    aRect.size.height -= kbSize.height;
    if (!CGRectContainsPoint(aRect, activeField.frame.origin) ) {
        [self.scrollView scrollRectToVisible:activeField.frame animated:YES];
    }
}

- (void)keyboardWillBeHidden:(NSNotification*)aNotification
{
    UIEdgeInsets contentInsets = UIEdgeInsetsMake(64.0, 0.0, 0.0, 0.0);
    scrollView.contentInset = contentInsets;
    scrollView.scrollIndicatorInsets = contentInsets;
}

- (void)textFieldDidBeginEditing:(UITextField *)textField
{
    activeField = textField;
}

- (void)textFieldDidEndEditing:(UITextField *)textField
{
    activeField = nil;
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
