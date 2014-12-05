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
        session = [SCSession defaultSession];
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
    
    firstNameTextField.delegate = self;
    lastNameTextField.delegate = self;
    emailTextField.delegate = self;
    phoneTextField.delegate = self;
    
    [self registerForKeyboardNotifications];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    [state addObserver:self forKeyPath:@"status" options:0 context:nil];
    [profile addObserver:self forKeyPath:@"updateStatus" options:0 context:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(sessionUpdated) name:@"scsession_updated" object:session];
}

- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
}

- (void)sessionUpdated {
    if (session.exists) {
        [profile sendUpdates];
    } else if (session.createFailed) {
        
    } else if (session.destroyFailed) {
        
    }
    [[NSNotificationCenter defaultCenter] removeObserver:self name:@"scsession_updated" object:session];
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
        [phoneTextField.text isEqual:@""]) {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:nil
                                                        message:@"You must enter all fields."
                                                       delegate:nil
                                              cancelButtonTitle:@"OK"
                                              otherButtonTitles:nil, nil];
        [alert show];
    } else if (!match) {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:nil
                                                        message:@"Please enter a valid email."
                                                       delegate:nil
                                              cancelButtonTitle:@"OK"
                                              otherButtonTitles:nil, nil];
        [alert show];
    } else {
        [profile stageUpdatedFirstName:firstNameTextField.text];
        [profile stageUpdatedLastName:lastNameTextField.text];
        [profile stageUpdatedEmail:emailTextField.text];
        [profile stageSupplementalValue:phoneTextField.text forKey:@"phone"];
        [state loginWithIdentifier:emailTextField.text zipcode:@""];
        
    }
}

- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary *)change context:(void *)context {
    if ([keyPath isEqualToString:@"status"]) {
        if (state.status == SCRegStatusSuccess) {
            [session create];
            [state removeObserver:self forKeyPath:@"status"];
        }
    } else if ([keyPath isEqualToString:@"updateStatus"]) {
        if (profile.updateStatus == SCProfileRemoteSuccess) {
            [self createAccount];
            [profile removeObserver:self forKeyPath:@"updateStatus"];
        }
    }
}

- (void)createAccount {
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:nil message:@"You have been registered" delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil, nil];
    [alert show];
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (IBAction)doneButtonPressed:(id)sender {
    [self.view endEditing:YES];
}

- (IBAction)previousButtonPressed:(id)sender {
    NSInteger tag = activeField.tag - 1;
    
    UITextField *textField = (UITextField *)[self.view viewWithTag:tag];
    
    if (textField) {
        [textField becomeFirstResponder];
        activeField = textField;
    }
}

- (IBAction)nextButtonPressed:(id)sender {
    NSInteger tag = activeField.tag + 1;
    
    UITextField *textField = (UITextField *)[self.view viewWithTag:tag];
    
    if (textField) {
        [textField becomeFirstResponder];
        activeField = textField;
    }
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


@end
